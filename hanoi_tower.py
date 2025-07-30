#This is a simple version of the Tower of Hanoi game made with Python, using Tkinter.
#At the start, the player chooses a difficulty: Easy, Normal, or Hard.
#The number of disks depends on the difficulty selected.
#The goal is to move all the disks from the first tower to the second or third one.
#You can only move one disk at a time, and you can't place a bigger disk on a smaller one.
#The player moves the disks by clicking on the towers.
#If all the disks are stacked correctly on the second or third tower, the game shows a "You win!" message.

#imports
import tkinter

class HanoiTower:

    #Constructor for the HanoiTower class to initialize the variables and set up the game.
    def __init__(self, root):

        #Initiation of the canvas.
        root.title("Tower of Hanoi")
        root.resizable(False, False)
        window_height = 300 
        window_width = 600
        self.canvas = tkinter.Canvas(root, width = window_width, height = window_height)
        self.canvas.pack()

        #Create the selection rectangle.
        self.selection = self.canvas.create_rectangle(0, 0, 200, 300, outline = "", fill = "darkgray")
        self.canvas.itemconfigure(self.selection, state = 'hidden')

        #Bind mouse clicks to the mouseClick function.
        self.canvas.bind("<Button-1>", self.mouseClick)

        #variables
        self.win = False
        self.selected_tower = 0
        self.towers = [ [], [], [] ]
        self.difficulty = 0
        self.difficulty_selected = False
        self.disks = []
        self.colors = ["white", "lightskyblue", "steelblue", "cyan", "blue", "teal"]
        self.texts = ["Easy", "Normal", "Hard"]
        self.select_difficulty()

    #This function displays the difficulty options on the screen.
    def select_difficulty(self):
        x = 100
        y = 150
        for i in self.texts:
            self.canvas.create_text(x, y, text = i, font = ('Arial', 30, 'bold italic'))
            x += 200

    #This function starts the game after selecting the difficulty.
    def draw_board(self):

        #Initialize temporary variables and clear the canvas.
        for item in self.canvas.find_all():
            if item != self.selection:
                self.canvas.delete(item)
        num = [1, 2, 3]
        x = 95
        z = 3

        #Create the towers on the canvas.
        for i in range(3):
            self.canvas.create_rectangle(x, 75, x + 10, 250, fill = "black")
            x += 200
        self.canvas.create_rectangle(2, 250, 601, 300, fill = "black")

        #Create the disks based on the difficulty selected.
        for i in range(self.difficulty):
            z += 1
            num.append(z)
        num.reverse()

        for i in num:
            self.towers[0].append(i)
            y = 250 - (len(self.towers[0]) - 1) * 15
            disk = self.canvas.create_rectangle(65 - i * 10, y, 135 + i * 10, y - 15, fill = self.colors[i - 1])
            self.disks.append(disk)
        self.disks.reverse()

    #This function moves a disk to the correct position on the screen.
    def draw_disk(self, disk_size, tower):
        y = 250 - (len(self.towers[tower - 1])) * 15
        self.canvas.coords(self.disks[disk_size - 1], 65 - disk_size * 10 + 200 * (tower - 1), y, 135 + disk_size * 10 + 200 * (tower - 1), y - 15)

    #This function handles the mouse clicks for selecting and moving disks.
    def mouseClick(self, event):

        #Get the mouse position and determine the column clicked.
        mousex = event.x
        column = mousex // 200 + 1

        #Check if the difficulty has been selected and if the game is not won.
        if self.difficulty_selected:

            if not self.win:

                #If a column hasn't been selected yet and the tower clicked has disks, select that tower.
                if self.selected_tower == 0 and not len(self.towers[column - 1]) == 0:
                    self.canvas.coords(self.selection, 200 * (column - 1), 0, 200 * column, 300)
                    self.canvas.tag_lower(self.selection)
                    self.canvas.itemconfigure(self.selection, state = 'normal')
                    self.selected_tower = column

                #If a column hasn't been selected and the tower clicked is empty, do nothing.
                elif self.selected_tower == 0 and len(self.towers[column - 1]) == 0:
                    return

                #If a column has been selected:
                else:

                    #If the clicked column is the same as the selected tower, deselect it.
                    if self.selected_tower == column:
                        self.selected_tower = 0
                        self.canvas.itemconfigure(self.selection, state = 'hidden')

                    #If the clicked column is different from the selected tower and the move is valid (placing a smaller disk on a bigger one or on an empty tower), move the disk.
                    elif len(self.towers[column - 1]) == 0 or self.towers[self.selected_tower - 1][-1] < self.towers[column - 1][-1]:
                        self.draw_disk(self.towers[self.selected_tower - 1][-1], column)
                        self.towers[column - 1].append(self.towers[self.selected_tower - 1][-1])
                        del self.towers[self.selected_tower - 1][-1]
                        self.selected_tower = 0
                        self.canvas.itemconfigure(self.selection, state = 'hidden')

                    #If the move is invalid (placing a bigger disk on a smaller one), deselect the tower.
                    else:
                        self.selected_tower = 0
                        self.canvas.itemconfigure(self.selection, state = 'hidden')

                #Check if the player has won.
                self.detect_win()

        #If the difficulty has not been selected, set it based on the column clicked.
        elif 0 < column < 4:
            self.difficulty = column
            self.difficulty_selected = True
            self.draw_board()

    #This function checks if the player has won the game and displays a win message.
    def detect_win(self):
        for i in range(2):
            if self.difficulty == 1 and self.towers[i + 1] == [4, 3, 2, 1] or self.difficulty == 2 and self.towers[i + 1] == [5, 4, 3, 2, 1] or self.difficulty == 3 and self.towers[i + 1] == [6, 5, 4, 3, 2, 1]:
                self.win = True
                self.canvas.delete("all")
                self.canvas.create_text(300, 150, text = "You win!", font = ('Arial', 30, 'bold italic'))

#If this script is run directly, create a Tkinter window and start the game.
if __name__ == "__main__":
    root = tkinter.Tk()
    game = HanoiTower(root)
    root.mainloop()