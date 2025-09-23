# Installation Guide for DeepMode ⚡

## Introduction 📖

This guide explains how to upload and run the DeepMode project on your hardware.  
The project consists of a single `.ino` file that contains the entire source code.  
DeepMode itself runs on the hardware (Arduino/ESP32), but it is installed **via a computer** using the Arduino IDE (desktop or web version).

## Installation types 💻

DeepMode can be installed onto your hardware using a computer with the Arduino IDE or the Arduino Web Editor.

| **Type** | **Description** | **More information** |
| -------- | ---------------- | ------------------- |
| Arduino IDE (Windows, macOS, Linux) | Use the Arduino IDE (desktop app) to compile and upload the `.ino` sketch to your hardware | [Installation steps](#installation-steps) |
| Arduino Web Editor 🌐 | Use the [Arduino Web Editor](https://create.arduino.cc/editor) to compile and upload the `.ino` sketch directly from your browser | [Installation steps](#installation-steps) |

## System requirements 🛠️

- A computer with Windows, macOS, or Linux 🖥️ (used only to install DeepMode onto the board)  
- Either:  
  - [Arduino IDE](https://www.arduino.cc/en/software) installed (latest version recommended) 💾  
  - Or access to the [Arduino Web Editor](https://create.arduino.cc/editor) 🌐  
- Supported hardware (Arduino or ESP32 board) 🔌  
- USB cable to connect the board to your computer 🔗  

## Before you begin ✅

Make sure you have:  

* Installed the Arduino IDE 💻 **or** signed in to the Arduino Web Editor 🌐  
* Connected your board via USB 🔌  
* Installed the correct board support package (Arduino AVR Boards, ESP32, etc.) 📦  

## Installation steps 🚀

### Option A – Desktop IDE 💾

1. **Install Arduino IDE**  
   Download and install the [Arduino IDE](https://www.arduino.cc/en/software) for your operating system.  
2. **Open the project file**  
   Open the `.ino` file included in this repository with the Arduino IDE 📂.  
3. **Select your board and port**  
   Go to **Tools → Board** and choose your board (e.g., Arduino Uno or ESP32).  
   Also select the correct **Port** 🎛️.  
4. **Compile the code**  
   Click the ✅ (check mark) button in the Arduino IDE to verify/compile the sketch ⚙️.  
5. **Upload to your hardware**  
   Click the → (right arrow) button to upload the sketch ⬆️.  

### Option B – Web Editor 🌐

1. **Sign in to the [Arduino Web Editor](https://create.arduino.cc/editor)**.  
2. **Upload the `.ino` file** to your workspace 📂.  
3. **Select your board and port** from the toolbar 🎛️.  
4. **Click "Verify"** to compile the sketch ⚙️.  
5. **Click "Upload"** to flash the program to your board ⬆️.  

## Verify installation 🔍

- The Arduino IDE or Web Editor should display **"Done uploading"**.  
- Your hardware (Arduino/ESP32 board) should now automatically run the DeepMode program 🎉.  

## Uninstallation options 🗑️

To remove DeepMode, simply upload a blank sketch or another program to the board.

## Troubleshooting 🐞

### Problem: Board not detected  
- **Cause**: Missing driver or wrong USB cable.  
- **Solution**: Install the necessary USB drivers for your board and make sure you are using a data-capable USB cable.  

### Problem: Compilation error  
- **Cause**: Missing board support package.  
- **Solution**: Install the correct board package via **Tools → Board → Board Manager** (desktop IDE) or via the Web Editor settings.  

## Next steps 🎯

After a successful installation, you can start customizing the `.ino` file to fit your project needs.  
For collaboration, please refer to our contribution guide (if available).

---
