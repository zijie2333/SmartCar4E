This technology innovation course is based on the development of smart cars based on PSoC4 and its expansion boards. Required tasks to be implemented include two parts：the **line patrol** and the **labyrinth walking**. 


The hardware relies on various sensors and drive modules on the smart car, including infrared ranging sensors, infrared line sensors, ultrasonic sensor，encoder, collision sensor and PWM module. Additionally, there are also display debugging modules, such as LCD module, USB serial communication module,etc.


The software mainly relies on **Cypress Semiconductor**'s **PSoC Creator integrated development software** to complete peripheral module building, pin configuration and program Compile,etc.



Each module consists of a **header file** named "module_name.h" and an **implementation file** named "module_name.c". The module contains at least the "module_name_init()" function and the "module_name_feature()" function to enable and enable module-related devices and initialization.
