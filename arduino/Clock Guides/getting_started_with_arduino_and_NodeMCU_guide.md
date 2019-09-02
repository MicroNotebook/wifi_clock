# Background

The Arduino IDE (integrated development environment) is a beginner friendly text editor and compiler for the Arduino language. Arduino is a language almost identical to C++ (a common programming language).

# Requirements
You must first download the drivers for your operating system so the microcontroller and communicate with your computer. Look on the bottom of your NodeMCU board for the type of driver chip you have. If you have the CH340G version, you can download the drivers for your operating system from [this](https://github.com/nodemcu/nodemcu-devkit/tree/master/Drivers) github page. If you have the CP2102 version, you can download the drivers for you operating system from [this](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) website. Simply download the ZIP file, extract it, then double click the application to run it.

# Arduino Download

Download the latest version of the Arduino IDE from [here](https://www.arduino.cc/en/Main/Software). Simply scroll down and select your operating system. After selecting the  operating system, it will ask you if you wish to donate. If you do not wish to donate, you can click *Just Download* to download for free.

# Installation

### For Windows
Click on the downloaded .exe file after it finishes downloading. If your device asks if you want to allow this app to make changes to your device, click yes. You will then be prompted to select which components to install. The defaults will be fine, so click next. You will then be prompted where you wish to install the components. You can choose to modify this, but the default is usually fine. Click install when you are ready. When the installation is finished, click close if the window does not close on its own.

### For Mac
Extract the downloaded zip file. Copy the Arduino Application into the your Applications folder.

### For Linux
Extract the downloaded zip file. Open the arduino-1.x.x folder extracted from the zip file. Right click on the install.sh file and choose **Run in Terminal**. If this option is not present on your Linux version, you will have to open a terminal, navigate to this directory, and type **./install.sh**.

# NodeMCU Configurations
Open the Arduino IDE and click on the **File** tab. From there, select **Preferences**. In the **Additional Boards Manager URLs**, enter: http://arduino.esp8266.com/stable/package_esp8266com_index.json. If you have other URLs listed here already, you can enter a space and a comma to separate them. Click *OK* when done.

Next, select the **Tools** tab. Scroll over **Board** and click on **Board Manager**. In this new menu, type **esp8266** in the *Filter your search* field. Select the most recent version, then click **Install**.

The last step is to set the NodeMCU as our current board. Select the **Tools** tab and scroll down to the **Board** tab. Scroll down through all the boards until you find the **NodeMCU 1.0 (ESP-12E Module)** board and click on it.

# Installing Libraries
Two libraries the clock board uses are the **LedControl** and **Ticker** libraries. Libraries are files that contain sets of like functions. For instance, the **Ticker** library allows us to use timers on our board and the **LedControl** library allows us to easily set the 7-segment displays.

Select the **Sketch** tab from the top menu and scroll down to **Include Libraries**. Click on the **Manage Libraries** tab. In the new window, type **LedControl** into the *Filter your search* field. Select the most recent version, then click **Install**. Depending on the version of Arduino you have downloaded, you might already have the **Ticker** library installed when you downloaded the newest firmware for the **ESP8266**. To check this, follow the same steps as you did for downloading the **LedControl** library, except type in **Ticker**. If nothing comes up, you already have the library. Otherwise, install the newest version. You can now close the window.

You are now ready to start writing your first program!