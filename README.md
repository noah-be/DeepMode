# DeepMode ⚡

## Project description 📖

DeepMode is a prototype project that tackles the modern challenge of focus in a world full of stress, distractions, and pressure.  
It fosters mindfulness and self-reflection 🌱, helps users manage daily stress 🧘, and empowers them to concentrate on what truly matters 🎯.  
Currently in the validation and iteration phase 🔧, DeepMode is building Prototype 2.0, running first pilot tests 👥, and integrating expert perspectives 🧑‍⚕️ to refine its positioning.  

### System Overview 🖼️

Below you can see a simple overview of the current prototype hardware:  

```mermaid
flowchart TB
    user([User])

    subgraph device["DeepMode Device (Hardware)"]
        esp32[ESP32 Microcontroller]
        btnL[Button Left]
        btnR[Button Right]
        oled[OLED Display (I²C)]
        battery[Battery / USB Power]
    end

    user -->|press| btnL
    user -->|press| btnR

    btnL --> esp32
    btnR --> esp32
    oled <-->|SDA/SCL| esp32
    battery --> esp32
    battery --> oled

## Who this project is for 👥

This project is intended for people who experience stress, distractions, or difficulties with focus.  
We are currently in the process of refining and defining the exact target group through research and pilot testing 🔍.  

## Project dependencies 🛠️

Before using DeepMode, ensure you have:  

* An Arduino or ESP32 board ⚡  
* A USB cable to connect the board 🔌  
* [Arduino IDE](https://www.arduino.cc/en/software) (desktop) 💻 or [Arduino Web Editor](https://create.arduino.cc/editor) 🌐  
* The required 3D-printed parts 🖨️ (see `/3d-files` folder for STL and Blender files)  

## Instructions for using DeepMode 🚀

At this stage, DeepMode does not yet include a full onboarding process.  
The project can already be installed and tried out in its current prototype state, and we actively welcome feedback 💬.  

Feedback can currently be shared via Slack directly with one of the [team members](./OUR-TEAM.md).  

A detailed installation guide is available in [`INSTALLATION.md`](./INSTALLATION.md).  

## Troubleshooting 🐞

If you encounter problems, please check the [installation guide](./INSTALLATION.md) for tips and troubleshooting steps.  
You can also reach out via Slack to a [team member](./OUR-TEAM.md).  

## Contributing guidelines 🤝

We welcome contributions of all kinds — from testing 🧪 and design 🎨 to development and documentation 📚.  
Please get in touch with the team via Slack before starting to contribute.  

## Additional documentation 📑

* [Installation Guide](./INSTALLATION.md)  
* [Our Team](./OUR-TEAM.md)  

## How to get help 🆘

For support, questions, or feedback, please contact the [DeepMode team](./OUR-TEAM.md) via Slack.  

## Terms of use 📜

DeepMode is licensed under the [MIT License](./LICENSE).  

---
