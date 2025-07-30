#This is a simple virtual version of the puzzle "Game 15", created with Python, using Tkinter.
#The game randomly scrambles 15 tiles with numbers in a 4x4 grid, with one empty space. 
#The player clicks the tiles to move them into the empty space, while trying to arrange the numbers in order from 1 to 15 (lowest to highest). 

#Imports
import tkinter
import random

#Class Game15 represents the game state and logic.
class Game15:

    #Constructor function which initializes the game state.
    def __init__(self, root):

        #Initiation of the canvas.
        root.title("Game 15")
        root.resizable(False, False)
        self.canvas = tkinter.Canvas(root, width = 460, height = 460)
        self.canvas.pack()

        #This binds the left mouse click to the function mouseClick.
        self.canvas.bind("<Button-1>", self.mouseClick)

        #Initialization of the grid and the game state.
        self.spot_state = ["x"] * 16
        self.moveable_spots = [ (2, 5), (1, 3, 6), (2, 4, 7), (3, 8), (1, 6, 9), (2, 5, 7, 10), (3, 6, 8, 11), (4, 7, 12), (5, 10, 13), (6, 9, 11, 14), (7, 10, 12, 15), (8, 11, 16), (9, 14), (10, 13, 15), (11, 14, 16), (12, 15) ]
        self.spots = []
        self.game_over = False
        self.scramble_quantity = 5000
        self.draw_grid()
        self.scramble_tiles()

    #This for loop makes the grid pattern.
    def draw_grid(self):
        liney = 115
        linex = 115

        #This for loop draws the lines of the grid.
        for i in range(3):
            self.canvas.create_line(linex, 0, linex, 460)
            self.canvas.create_line(0, liney, 460, liney)
            linex += 115
            liney += 115

        #This for loop draws the numbers on the tiles.
        for i in range(16):
            x=(i % 4) * 115 + 57.5
            y=(i // 4) * 115 + 57.5
            if i < 15:
                text = self.canvas.create_text(x, y, text = i + 1, font = ('Arial', 30, 'bold italic'))
                self.spot_state[i] = i + 1
            else:
                text = self.canvas.create_text(x, y, text = "", font = ('Arial', 30, 'bold italic'))
            self.spots.append(text)

    #Function scramble_tiles shuffles the tiles at the start of the program.
    def scramble_tiles(self):
        for _ in range(self.scramble_quantity):
            spot_num = random.randint(1, 16)
            if not self.spot_state[spot_num - 1] == "x":
                for i in self.moveable_spots[spot_num - 1]:
                    if self.spot_state[i - 1] == "x": 
                        self.spot_state[i - 1] = self.spot_state[spot_num - 1]
                        self.canvas.itemconfig(self.spots[i - 1], text = self.spot_state[spot_num - 1])
                        self.canvas.itemconfig(self.spots[spot_num - 1], text = "")
                        self.spot_state[spot_num - 1] = "x"
                        break

    #Function mouseClick registers and handles the left mouse click.
    def mouseClick(self, event):

        mousex = event.x
        mousey = event.y
        row = mousey // 115
        col = mousex // 115
        spot_num = row * 4 + col + 1

        if 0 <= row < 4 and 0 <= col < 4:
            if not self.game_over:
                for i in self.moveable_spots[spot_num - 1]:
                    if self.spot_state[i - 1] == "x":
                        self.spot_state[i - 1] = self.spot_state[spot_num - 1]
                        self.canvas.itemconfig(self.spots[i - 1], text = self.spot_state[spot_num - 1])
                        self.canvas.itemconfig(self.spots[spot_num - 1], text = "")
                        self.spot_state[spot_num - 1] = "x"
                        break
                self.check_for_win()

    #Function check_for_win checks if the player has completed the puzzle, and if so, displays a victory message.
    def check_for_win(self):
        if all(self.spot_state[i] == i + 1 for i in range(15)):
            self.game_over = True
            self.canvas.delete("all")
            self.canvas.create_text(460 / 2, 460 / 2, text = "You won!", font = ('Arial', 40, 'bold'))


#If this file is run directly, it creates a Tkinter window and starts the game.
if __name__ == "__main__":
    root = tkinter.Tk()
    game = Game15(root)
    root.mainloop()
