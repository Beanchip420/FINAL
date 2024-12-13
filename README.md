Project Documentation:

Inside of this Repository is my work for creating Tetris on the stm32f429i microcontroller. Something to note is that this was a Final Project established by the University of Colorado.
As a result a large part of the code was given to students to get started and build the game Tetris from it. So, specifc to this project documentation I will only be describing
code that I completed/modified. To the best of my knowledge these are the files that I modified or created and included is a description of the functionality of each respective file. 
An overarching overview of my project has to be three different screens. The first screen is a title page saying "Tap to Play." Not only that but all the shapes are also displayed
on this screen with their respective colors. Once the screen is pressed once, remmeber that I have interrupts set for the touch screen (EXTI 15) then my start flag is set to 1 and the 
second screen starts by adding "Start" to my scheduler. The start flag is in place because if it is set then play the game and thus never return to the start screen unless the board is reset. In 
the second screen I have two other major interrups, timer2 and the user button. If button is pressed in EXTI 0 adds Rotate CC to my scheduler. Every 3 seconds the timer raises an interrupt
and in my IRQ handler for this I add "Count" to my scheduler. Once the game ends, if my board has at least a single 1 on the top row then the third screen is scheduled which displays the elapsed
time that is from timer 5 which I initilized and started once my Start flag was set

main.c/h:

This is the entry to my Tetris project. While I do not do it in this file there was a compile switch in one of the files given to us by the Professor to initilize both the LCD screen
interrupt and the LCD Screen itself. Most of the functions in my main file/function were provided by the class however I did write my "First Screen" in the application init. Simple screen
I mainly used pre written LCD driver functions to draw all the shapes. Again once the screen is pressed once then my start flag is set and will remain set until the board is reset. really
the main file handles all the removing of the scheduled events and inside of each get scheduled events running appropriete functions. 

ApplicationCode.c/h:

The only real modifications to this file worth talking about other than the start screen has to be the IRQ handlers that I wrote for the button as well as the timer. In each handler
a respective event is scheduled to be run. Not only that but a good amount of peripherals are initized here, specifc to what I wrote I initilized timer 2 as a interrupt, timer 5, Button
as an interrupt, and also the random number generator. 

InterrupControl.c/h:

Not much changed here, I copied file over from past labs. This interrupt control is a personal written file that lowers, modifies, and bit bangs specifc to the NVIC and other interrupt
hardware. I most likley should not have used this and instead used HAL code, however I understood my own work better than the specifc hal driver interrupt functions so I kept it. 

Tetris.c/h:

This is where my game logic and really my final project lives. This script extensively calls and uses scripts below it as well as files provided to us from the teaching staff. A quick overview
of this function has to be the extensive use of a single block structure , volatile flags, and a lot of static variables. Delving deper into the block structure this was a tyedef structure
which held the current shape that was actively allowed to be modified by the user, x and y positions, and color of the specifc shape. It is important to note that I turned this structure
into a static variable that I consistenly used in my C file. In my C file I made static variables of all my shpaes which I placed in 4x4 arrays and also a 16x12 board matrix which alowed me 
to have each "Block" be a 20x20 pixel. To start the game the Gen_RandomNumber function from my RNG file is called and the number returned is modulod by 7 thus giving me a number from 0-6. 
Each number corresponds to one of the 7 specifc shapes represented in tetris. I wrtoe a quick switch statement that sets one of the variables defined as static variables to the value of my
"Current_Shape" inside of my block structue. From here the timer interrupt is started and the game plays with the current shape falling every 3 seconds and able to be moved left, right, or rotated clockwise
90 degrees. The down movement and left and right movement, for the most part, were copied and pasted functions. The reason is because due to the numerous static variables set, at any timer
interrupt the space below the block was checked. To do this I iterated through my 4x4 current shape array and I found the farthest filled in(at least 1 element in the matrix is set) coloum on the left, farthest
filled in coloum on the right, lowest row filled in and highest row filled in. As a result my general collision logic was checking to see the larger board matrix had a one either one position below, one position to the left,
or one position to the right of any movement of my current shape. If my shape is going to hit a "Filled" in space with my board which would only happen if it was a border. the bottom 
floor, or another piece I would stop timer 2 update my board with the current shapes current position restart timer 2 and begin dropping another randomly chosen shape. This will continue until the 
very first row of the larger board matrix has at least a single set element. If this is set then raise my endgaame flag which stops my timer 5 and I have some specifc algorithm that converts
the clock count value back into seconds. This value in seconds is then transformed from an integer to a strig array and displayed to the screen along with a messege that says to reset the board
to play again. When I hit my endgame I call a Hal Delay function that sits at the end screen for about 15 seconds or so bascially forcing the user to reset. 

Scheduler.c/h:

Not much changed here, I copied file over from past labs. The scheduler really made my life easier specifically because I could add scheduled events in each IRQ handler. This made it both
effective and effecient due soley that my code was not hanging for a long time in my handlers. The only real change was creating macros for specifc events such as COUNT, ROTATE_CC, MOVE_RIGHT, 
MOVE_LEFT, and etc... 


LCD_Driver.c/h:

Not much changed here from the provided code. The only real difference is that my "First Screen" is written here and called in my application code files. The reason I wrote my start screen
here instead of anywhere else is because the "First Screen" was the first function I wrote so I was still trying to figure out the hierachy for my project. Not to mention that my 
"First Screen" I wrote it soley from provided functions such as LCD_DisplayChar, LCD_Draw_Pixel, and etc... The other important function I wrote was a Draw_Block function
which basically drew a 20x20 inputted color pixel block in the provided x and y position as inputs as well.  

Timer.c/h:

This file was copied and pasted from previous lab work. The only real changes is that in my Timer_Init function I initilize both timer 2 and 5, one as an interrupt which will trigger 
an interrupt every 3 seconds and the other as a straight counter that soley counts up. Apart from the ARR value and how they are started (interrupt or not) they are configured the same with the same 
counter mode, clock divider, prescaler, and etc. Due to some of the provided code it made my Peripheral clock speed PLCK 84 MHz so all my ARR, prescalar, and etc were computed using 
the 84 MHz for the clock frequency. Also another change is that most of this file when copied was specifc code that bit banged specifc bits in a specifc timer peripheral, I changed my written
functions to call hal functions intead.

Button_Driver.c/h:

This file was copied and pasted from previous lab work, this was the only file that I didn't even touch. File basically configures and initlized the button to be an interrupt on the rising edge.

RNG.c/h:

Really simple function, I intizilized this peripheral and also wrote a function that generated a gen number that retured said general number. This function is not really special because
I did just call a specifc Hal function related to the RNG. 

stm32f4xx_hal.h + other provided code. 

LINK TO FINAL REPO: https://github.com/Beanchip420/FINAL

