# Includes simple projects on FreeRTOS with Bare-Metal programming on STM32F407G-DISC1 Discovery kit with STM32F407VG MCU

## Preperation

To add the freertos header file into the STM32 project on STM32CubeIDE, follow the below steps:
1. Download FreeRTOS: First, ensure you have downloaded the FreeRTOS source files. You can get them from the official FreeRTOS website.

2. Include FreeRTOS Files in Your Project:

    -In STCubeIDE, navigate to your project in the Project Explorer.
    -Right-click on your project and select "Properties".
    -Go to "C/C++ General" -> "Paths and Symbols" -> "Includes" tab.
    -Click on "Add" and navigate to the folder where you have the FreeRTOS source files and include it.
    -Make sure to include the folder containing FreeRTOS.h in your project's include paths.

3. Configuration:

    -Ensure you have configured FreeRTOS properly for your STM32 microcontroller. This usually involves editing the FreeRTOSConfig.h file to set up things like heap size, tick frequency, etc., according to your application's requirements.

4. Update Compiler Include Paths:

    -Go to "C/C++ Build" -> "Settings" -> "Tool Settings" -> "MCU GCC Compiler" -> "Includes".
    -Add the path to the directory containing FreeRTOS header files.

5. Add FreeRTOS Source Files to the Build:

    -In the Project Explorer, right-click on your project and select "Properties".
    -Go to "C/C++ General" -> "Paths and Symbols" -> "Source Location" tab.
    -Click on "Link Folder" and navigate to the folder containing the FreeRTOS source files.
    -Make sure the folder is linked to your project.
