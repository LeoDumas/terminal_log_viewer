# Terminal Log Viewer

**This project is currently in development.**

A simple terminal-based log file viewer built with **C++** and **FTXUI**. 


## Features

- Load and display log files
- Search functionality to filter log entries
- Interactive UI with keyboard shortcuts

## Building

Ensure you have CMake and a C++ compiler installed.

Run the build script:

``` bash
chmod 741 ./start_build.sh # if necessary
./start_build.sh
# Or 
./start_build.sh -rebuild # If rebuilding the project is necessary
```

This will configure and build the project using Ninja.

**This doesn't me that the tool will be installed globally on your device !**

Usage
Run the executable with a log file as an argument:

```bash
./build/LogViewer /path/to/logfile.log
```

Shortcuts

* **/** : Focus on search bar

* **Esc** : Leave search and focus on log list

* **q** : Quit the application

## Future Plans

In the future, the program may be invoked using the tlv command for easier access.