#include <atomic>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/component/event.hpp" 
#include "ftxui/dom/elements.hpp"

using namespace ftxui;

int main(int argc, char **argv) {
  auto screen = ScreenInteractive::Fullscreen();

  // Load File Data
  if (argc != 2) {
    std::cerr << "Missing arguments" << std::endl;
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file) {
    std::cerr << "Could not open file" << std::endl;
    return 1;
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  // Search logic
  std::string search_query;
  int selected_line = 0;
  std::vector<std::string> filtered_lines = lines;

  InputOption input_option;
  input_option.on_change = [&] {
    filtered_lines.clear();
    for (const auto &l : lines) {
      if (l.find(search_query) != std::string::npos) {
        filtered_lines.push_back(l);
      }
    }
    selected_line = 0;
  };

  auto search_input = Input(&search_query, "Search: ", input_option);

  // Log Component
  auto log_menu = Menu(&filtered_lines, &selected_line);

  int log_selector = 1; // Start with focus on logs list

  auto log_container = Container::Vertical({
      search_input,
      log_menu,
  }, &log_selector);

  auto log_renderer = Renderer(log_container, [&] {
    return vbox({
        hbox({
            text(" grep > ") | center, 
            search_input->Render()
        }) | border,
        separator(),
        filtered_lines.empty()
            ? text("No matches found.") | center
            : log_menu->Render() | vscroll_indicator | frame | flex
    });
  });

  // Layout
  int tab_index = 0;
  std::vector<std::string> tab_entries = {"Log view"};

  auto tab_selection = Menu(&tab_entries, &tab_index, MenuOption::HorizontalAnimated());

  Components tab_children;
  tab_children.push_back(log_renderer);

  auto tab_content = Container::Tab(tab_children, &tab_index);

  auto main_container = Container::Vertical({
      tab_selection,
      tab_content,
  });

  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text("Terminal log viewer") | bold | hcenter,
        tab_selection->Render(),
        tab_content->Render() | flex,
        text("Shortcut: '/' to search, 'Esc' to list, 'q' to quit") | dim | center
    });
  });

  // Global Event Handler
  auto screen_quit = screen.ExitLoopClosure();

  auto main_with_shortcuts = CatchEvent(main_renderer, [&](Event event) {
    
    if(event == Event::q){
      screen_quit();
      return true;
    }

    // '/' to focus on search bar
    if (event == Event::Character('/') && log_selector != 0) {
      log_selector = 0;
      return true;
    }

    // Esc to leave search
    if (event == Event::Escape && log_selector == 0) {
      log_selector = 1;
      return true;
    }

    return false;
  });

  // Event Loop
  std::atomic<bool> refresh_ui_continue = true;
  std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.05s);
      screen.Post(Event::Custom);
    } 
  });

  screen.Loop(main_with_shortcuts);
  
  refresh_ui_continue = false;
  refresh_ui.join();

  return 0;
}
