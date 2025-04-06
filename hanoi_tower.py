#This is a simple version of the Tower of Hanoi game made with Python, using Tkinter.
#At the start, the player chooses a difficulty: Easy, Normal, or Hard.
#The number of disks depends on the difficulty selected.
#The goal is to move all the disks from the first tower to the third one.
#You can only move one disk at a time, and you can't place a bigger disk on a smaller one.
#The player moves the disks by clicking on the towers.
#If all the disks are stacked correctly on the third tower, the game shows a "You win!" message.

#imports
import tkinter

#variables
global towers,colors,selected,win,difficulty,difficulty_selected
win=0
selected=0
towers=[[],[],[]]
difficulty=0
difficulty_selected=False
disks=[]
colors=["white","lightskyblue","steelblue","cyan","blue","teal"]
texts=["Easy","Normal","Hard"]

#This function moves a disk to the correct position on the screen.
def draw_disk(disk_size,tower):
    global towers,colors,win
    y=250-(len(towers[tower-1]))*15
    canvas.coords(disks[disk_size-1],65-disk_size*10+200*(tower-1),y,135+disk_size*10+200*(tower-1),y-15)

#This function displays the difficulty options on the screen.
def select_difficulty():
    global texts, difficulty, difficulty_selected
    x1=100
    for i in texts:
        canvas.create_text(x1,150,text=i,font=('Arial',30,'bold italic'))
        x1+=200

#This function starts the game after selecting the difficulty.
def game_start():
    global towers,colors,win,difficulty,difficulty_selected
    canvas.delete("all")
    towers=[[],[],[]]
    num=[1,2,3]
    win=0
    x=95  
    y=3 
    for i in range(3):
        canvas.create_rectangle(x,75,x+10,250,fill="black")
        x+=200
    canvas.create_rectangle(2,250,601,300,fill="black")
    for i in range(difficulty):
        y+=1
        num.append(y)
    num.reverse()
    for i in num:
        towers[0].append(i)
        y=250-(len(towers[0])-1)*15
        disk=canvas.create_rectangle(65-i*10,y,135+i*10,y-15,fill=colors[i-1])
        disks.append(disk)
    disks.reverse()

#This function handles the mouse clicks for selecting and moving disks.
def mouseClick(event):
    global towers,colors,selected,selection,win,difficulty,difficulty_selected
    detect_win()
    mousex=event.x
    column=1+mousex//200
    if difficulty_selected:
        if win==0:
            if selected==0 and not len(towers[column-1])==0:
                selection=canvas.create_rectangle((column-1)*200,1,column*200,299,outline="",fill="darkgray")
                canvas.tag_lower(selection)
                selected=column
            elif selected==0 and len(towers[column-1])==0:
                detect_win()
                return
            else:
                if selected==column:
                    selected=0
                    canvas.delete(selection)
                elif len(towers[column-1])==0 or towers[selected-1][-1]<towers[column-1][-1]:
                    draw_disk(towers[selected-1][-1],column)
                    towers[column-1].append(towers[selected-1][-1])
                    del towers[selected-1][-1]
                    selected=0
                    canvas.delete(selection)
                else:
                    selected=0
                    canvas.delete(selection)
            detect_win()
    else:
        difficulty=column
        difficulty_selected=True
        game_start()

#This function checks if the player has won the game.
def detect_win():
    global win,towers,difficulty
    if difficulty==1 and towers[2]==[4,3,2,1] or difficulty==2 and towers[2]==[5,4,3,2,1] or difficulty==3 and towers[2]==[6,5,4,3,2,1]:
        win=1
        canvas.delete("all")
        canvas.create_text(300,150,text="You win!",font=('Arial',30,'bold italic'))

#Create the window and canvas.
canvas=tkinter.Canvas(width=600,height=300)
canvas.pack()

#Runs the select_difficulty function.
select_difficulty()

#Bind mouse clicks to the mouseClick function.
canvas.bind("<Button-1>", mouseClick)

#Runs the program.
tkinter.mainloop()
