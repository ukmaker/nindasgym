# nindasgym
A 3D printed gym with flashing lights, music and animation

All the gym equipment was printed from [TanyaAkinora's project](https://www.instructables.com/3d-Printed-Tiny-Gym/) - thanks Tanya!

[![The End Result](https://raw.githubusercontent.com/ukmaker/nindasgym/master/assets/IMG_1022.JPG)](https://youtube.com/watch?v=ekH63PJm3gI)
![In Action](https://youtube.com/watch?v=ekH63PJm3gI)

# A Reasonable Excuse
Why do something this silly? Hmm?

The story goes something like this:
  - The Dutch celebrate SinterKlaas on the 5th December as part of their Christmas tradition
  - One of the components of the celebrationis that there is a party
  - Each guest gets assigned (randomly and without the other knowing) another guest
  - The guests then make by hand a small suprise, write an accompanying poem and buy a small present
  - On the 5th, the recipients read their poem and receive their surprise and present
  - I know this because my Dutch neighbour told me, so it must be true
  - This was the second year for us to copy the tradition here in the UK
  - We may have gone a tiny bit overboard

My surprise recipient this year was my friend's sister Ninda who is a personal trainer. I started just with a cardboard box and the 3d printed gym equipment. Then I noticed I had a spare strip of 3-colour LEDS.......

# How Can I Make One?

1. Print the gym bits from Tetiana's project
2. Add extra ingredients
3. Bake until done

# The Recipe
## Ingredients
1. Tetiana's gym equipment
2. A cardboard box
3. Spray paint
4. 3-colour LED lighting strip - lengths to suit your box
5. A suitable power supply. I ended up using an 18V, 2A supply to make sure the stepper motor had enough oomph
6. A stepper motor. You'll need to experiment
7. One Arduino - pretty much anything will do
8. One stepper motor driver - [e.g. this A4988 one](https://reprapworld.co.uk/electronics/3d-printer-modules/stepper-drivers/a4988-stepper-motor-driver-carrier/?f=ms&mkwid=aGITQRal_dc%7Cpcrid%7C72636737008573%7Cpkw%7C%7Cpmt%7Cbe%7Cslid%7C%7Cprid%7CPF_92_8719345011504_POLOLU&pgrid=1162184743076999&ptaid=pla-4576236135429224&msclkid=d0e02402eb9218b8430e47b68c6f800f)
9. One [MP3 player module](https://www.amazon.co.uk/dp/B01N6P237G/ref=pe_27063361_485629781_TE_item)
10.  A small loudspeaker
11. A handful of components as per the schematic
12. You favourite protoyping board
13. Assorted bits of hardware for the lifting mechanism - e.g. small drawer slide, GT2 drive belt, pulley wheels.... 

## Method - Electronics
![Block Diagram](https://raw.githubusercontent.com/ukmaker/nindasgym/master/assets/BlockDiagram.PNG)
If you look at all the photos in the assets/ folder you'll see that I constructed the electronics on several small boards for ease of debugging:
 - A board holding the Atmega328 and associated support components. You can replace this directly with an Arduino if you like. I just happen to have a load of 328Ps and crystals etc, so it's cheap and easy for me to do this. I put the MP3 player
 module on this board also
 - A board holding the 7805 regulator and the LED driver transistors. I used ZTX650 transistors because I've had a box of them I'm been slowly getting through since 1980. You can use something more modern like ZTX618 or even 2N7000 (add 100K pull-downs on the gate if you do this).
 - A board holding the A4988 stepper driver

## Method - Mechanics
There was no method. I bodged stuff together until it worked. I had to swap the 12V power supply I was using for an 18V supply
literally at the last minute because the stepper just didn't have the power to lift the lid.

If I was to do this again (stop tittering in the back) I'd actually design it. There would be appropriate gearing.
Vital pieces of mechnanics would be properly attached, not held on with superglue/hotglue/screws through cardboard.

## Method - Firmware
I bought a CD copy of the Survivor album, ripped the Eye of the Tiger track and copied it to an SD card which goes in the MP3 player. The CD was part of Ninda's present.

I carefully timed how long it takes to get to the lyric "rising up" and programmed that into the Arduino sketch.

The sketch is triggered when the door is opened because there is a small microswitch which is activated when the door opens.

Closing the door causes the music to stop, the lights stop flashing and glow red and the lid goes back down.