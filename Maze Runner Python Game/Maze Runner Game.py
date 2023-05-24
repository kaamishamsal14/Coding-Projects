# -*- coding: utf-8 -*-
"""
Created on Sun May  1 15:51:35 2022

@author: kaami
"""

print("Use arrow keys or w,a,s,d to move player(purple square) to the red square")

try:
    num = int(input("Press any number to start game: "))
except:
    print("Invalid input! Press any number to start game: ")
else:
    import turtle
        
    game = turtle.Screen()
    game.setup(700,700)
    game.bgcolor("white")
    game.title("Maze Runner")
    
    #create pen
    class Pen(turtle.Turtle):
      def __init__(self):
        #initializing class
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("black")
        self.penup()
        self.speed(0)
    
    #create player
    class Player(turtle.Turtle):
      def __init__(self):
        #initializing class
        turtle.Turtle.__init__(self)
        self.shape("square")
        self.color("purple")
        self.penup()
        self.speed(0)
        
      def go_up(self):
          """"Make purple square go up a block"""
          move_to_x=player.xcor()
          move_to_y=player.ycor() + 24
        
          if (move_to_x,move_to_y) not in walls:
              self.goto(move_to_x, move_to_y)
            
          if (move_to_x,move_to_y) in fin_square:
              #turtle.bye()
              quit()
              print("")
              print("Congratulations! You have finished the game!")
      
      def go_down(self):
          """"Make purple square go down a block"""
          move_to_x=player.xcor()
          move_to_y=player.ycor() - 24
        
          if (move_to_x,move_to_y) not in walls:
              self.goto(move_to_x, move_to_y)
            
          if (move_to_x,move_to_y) in fin_square:
              #turtle.bye()
              quit()
              print("")
              print("Congratulations! You have finished the game!")
            
      def go_right(self):
          """"Make purple square go right one block"""
          move_to_x=player.xcor() + 24
          move_to_y=player.ycor()
        
          if (move_to_x,move_to_y) not in walls:
              self.goto(move_to_x, move_to_y) 
            
          if (move_to_x,move_to_y) in fin_square:
              #turtle.bye()
              quit()
              print("")
              print("Congratulations! You have finished the game!")
            
      def go_left(self):
          """"Make purple square go left one block"""
          move_to_x=player.xcor() - 24
          move_to_y=player.ycor()
        
          if (move_to_x,move_to_y) not in walls:
              self.goto(move_to_x, move_to_y)
        
          if (move_to_x,move_to_y) in fin_square:
              #turtle.bye()
              quit()
              print("")
              print("Congratulations! You have finished the game!")
            
    class Finish(turtle.Turtle):
        def __init__(self):
            #initializing class
            turtle.Turtle.__init__(self)
            self.shape("square")
            self.color("red")
            self.penup()
            self.speed(0)
            
    # class Spy(turtle.Turtle):
    #     def __init__(self):
    #         #initializing class
    #         turtle.Turtle.__init__(self)
    #         self.shape("square")
    #         self.color("blue")
    #         self.penup()
    #         self.speed(0)
    
    #create Levels list
    levels = [""]
    
    #define first level
    level_1 = [
    "XXXXXXXXXXXXXXXXXXXXXXXXX",
    "XP  XXX   XXX    XXXX XXX",
    "X X  XX X  XX XX XXXX   X",
    "X XX    XX  X XX  XX  X X",
    "X XX  X XXX   XXX XX XX X",
    "X X  XX XX XX    X X XX X",
    "X   XX  XX XXXXX   X XX X",
    "XX XX   X  XX   XX   X XX",
    "X  X   X      XXXXX  X  X",
    "X XX  X  XXXXX   XXX  X X",
    "X XX    XXX    X  XXX X X",
    "X XX X XX   XX XXXX   X X",
    "X    X X  X XX XX   X X X",
    "XX XX  X XX XX    XXX   X",
    "XX XX XX XX XXXXX  XX  XX",
    "XX  XX   X X    XX XXX XX",
    "X XX   X XXX XX  X X   XX",
    "X X  XXX XX  XXX  X XXX X",
    "X X  XX  X  XXXXX  X   XX",
    "X XX   XX  X   XXX X X XX",
    "X  XXX    XX X   X   XX X",
    "XX   XXXXXXX XXX X XX X X",
    "X X   X       XX X X    X",
    "X   X   XX  X          FX",
    "XXXXXXXXXXXXXXXXXXXXXXXXX"
    ]
    
    #Add maze to mazes list
    levels.append(level_1)
    
    #Create Level Setup Function
    
    def setup_maze(level):
      for y in range(len(level)):
        for x in range(len(level[y])):
          #Get the Character at each x,y coordinate
          #NOTE the order of the y and x in the next line
          character = level[y][x]
          #Calculate the screen x, y coordinates
          screen_x = -288 + (x * 24)
          screen_y = 288 - (y * 24)
          
          
          #Check if it is an X (representing a wall)
          if character == "X":
            pen.goto(screen_x, screen_y)
            pen.stamp()
            walls.append((screen_x,screen_y))
            
          if character == "P":
             player.goto(screen_x, screen_y)
             
          if character == "F":
              finish.goto(screen_x, screen_y)
              pen.stamp()
              fin_square.append((screen_x,screen_y))
              
          # if character == "S":
          #     spy.goto(screen_x,screen_y)
          #     pen.stamp()
          #     spy_square.append((screen_x,screen_y))
                     
    #class instances
    pen = Pen()
    player = Player()
    finish = Finish()
    # spy = Spy()
    
    
    # Walls
    walls=[]
    
    #finishing square
    fin_square=[]
    
    # spy_square=[]
    
    #Set up the level
    setup_maze(levels[1])
    
    def quit():
        global running
        running = False
    
    
    #Keyboard Binding
    turtle.listen()
    turtle.onkey(player.go_left,"a")
    turtle.onkey(player.go_left,"Left")
    turtle.onkey(player.go_right,"d")
    turtle.onkey(player.go_right,"Right")
    turtle.onkey(player.go_up,"w")
    turtle.onkey(player.go_up,"Up")
    turtle.onkey(player.go_down,"s")
    turtle.onkey(player.go_down,"Down")
    
    
    #Turn off screen upates
    game.tracer(0)
    
    running = True
    
    #Main Game Loop
    while running:
      # Update Screen
        game.update()
    game.bye()









