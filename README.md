# Virtual Keyboard for QT and C++ Based Projects for RaspberryPI Touchscreen

# Introduction

`Qt` is a popular cross-platform framework for building GUI applications. While Qt Creator is the official IDE for Qt development, many developers prefer using **Visual Studio Code** for its flexibility and extensive extensions. In this guide, we will walk through the process of setting up and building a virtual keyboard for Touchscreen based Usage of Qt application using **VS Code**. This Repo is based on the great work of [florisa](https://github.com/florisa/qt-widget-virtual-keyboard), we just modifyed the layout for a RaspberryPI Touchscreen. Thanks Therefore!

### Video Tutorial:
Comming Soon.

## Prerequisites

Before we start, ensure you have the following installed on your RaspberryPI:

* Qt 6 

* Visual Studio Code

* Qt Extension Pack for VS Code

* CMake

* A C++ Compiler (such as MinGW or MSVC)

### Step 1: Download this Repo
Open the Terminal in your project folder and run:
```bash
git clone ... 
```

### Step 2: Open VS Code.
In the current Terminal open VS Code:
```bash
code .
``` 

### Step 3: Run The Project
We have created a shell script `run_cmake.sh` which builds the project.
Therefore we need to change the mode of this file to an executable:
```bash
chmod +x run_cmake.sh
```
Now you can run build and run the project:
```bash
./run_cmake.sh
```
The binary file of the Project is in the folder /build/keyboard


### Step 6: Design the UI
When the building process succeed it will open the binary app keyboard and we are able to see a `LogIn System` Window. Using the keyboard you can type the Username and Password e.g. The Output will be printed on the command window. If you want to use the keyboard functionality in an another project, you just need to kopy the folder `keyboard` into your project and embed the keyboard by creating a QFrame for the keyboard in your ui_mainwindow.h file. Then you can create an instance of the keyboard in your mainwindow.cpp as shown in this example.

Open `ui_mainwindow.h` in VSCode and eddit the code as needed. Alternativaley you can work with the mainwindow.ui file Thererefore open Qt Designer and add two buttons: `OK` and `Cancel`. Change their object names to **btnOk** and **btnCancel**, respectively.

### Example Image

[![Image](/media/keyboard.png)](www.youtube.com/@BOMKE007)

