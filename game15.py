#This is a simple virtual version of the puzzle "Game 15", created with Python, using Tkinter.
#The game randomly scrambles 15 tiles with numbers in a 4×4 grid, with one empty space. 
#The player clicks the tiles to move them into the empty space, while trying to arrange the numbers in order from 1 to 15 (lowest to highest). 
#The program checks if the player won and displays a victory message when the puzzle is solved. 

import tkinter
import random

spot_state=["x","x","x","x","x","x","x","x","x","x","x","x","x","x","x","x"]
rand_spot=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
moveable_spots=[(2,5),(1,3,6),(2,4,7),(3,8),(1,6,9),(2,5,7,10),(3,6,8,11),(4,7,12),(5,10,13),(6,9,11,14),(7,10,12,15),(8,11,16),(9,14),(10,13,15),(11,14,16),(12,15)]
spots=[]
game_over=False

def mouseClick(event):
    mousex=event.x
    mousey=event.y
    row=mousey//115
    col=mousex//115
    spot_num=row*4+col+1
    if game_over==False:
        for i in moveable_spots[spot_num-1]:
            if spot_state[i-1]=="x":
                spot_state[i-1]=spot_state[spot_num-1]
                canvas.itemconfig(spots[i-1],text=spot_state[spot_num-1])
                canvas.itemconfig(spots[spot_num-1],text="")
                spot_state[spot_num-1]="x"
                break
        check_for_win()

def check_for_win():
    global game_over
    if all(spot_state[i]==i+1 for i in range(15)):
        game_over=True
        canvas.delete("all")
        canvas.create_text(460/2,460/2,text="You won!")

def scramble_tiles():
    global spot_state
    for nun in range(5000):
        spot_num = random.randint(1, 16)
        if not spot_state[spot_num-1]=="x":
            for i in moveable_spots[spot_num-1]:
                if spot_state[i-1] == "x": 
                    spot_state[i-1] = spot_state[spot_num-1]
                    canvas.itemconfig(spots[i-1], text=spot_state[spot_num-1])
                    canvas.itemconfig(spots[spot_num-1], text="")
                    spot_state[spot_num-1] = "x"
                    break

canvas=tkinter.Canvas(width=460,height=460)
canvas.pack()

liney=115
linex=115
for i in range(3):
    canvas.create_line(linex,0,linex,460)
    linex+=115
    canvas.create_line(0,liney,460,liney)
    liney+=115

for i in range(16):
    x=(i%4)*115+57.5
    y=(i//4)*115+57.5
    if i<15:
        text=canvas.create_text(x,y,text=i+1,font=('Arial',30,'bold italic'))
        spot_state[i]=i+1
    else:
        text=canvas.create_text(x,y,text="",font=('Arial',30,'bold italic'))
    spots.append(text)

scramble_tiles()

canvas.bind("<Button-1>", mouseClick)

tkinter.mainloop()
