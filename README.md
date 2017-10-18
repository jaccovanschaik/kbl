# kbl
Control keyboard backlight on an ASUS UX301L notebook.

The ASUS UX301L notebook has 4 levels of keyboard backlight, but it wasn't working for me on a vanilla xubuntu install. So I made this little program.

It can be called in one of these three ways:

  kbl <brightness>
    where <brightness> is a number from 0 to 3 inclusive. This sets the brightness directly.
  
  kbl --
    This reduces the brightness by one step.
    
  kbl ++
    This increases the brightness by one step.
    
It works by reading and writing the "/sys/class/leds/asus::kbd_backlight/brightness" file.
