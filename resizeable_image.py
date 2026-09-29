import imagematrix
import numpy as np

class ResizeableImage(imagematrix.ImageMatrix):
    def __init__(self, filename):
        super().__init__(filename)
        self.energy_cache = {}
    def energy(self,i,j):

        if (i,j) in self.energy_cache:
            return self.energy_cache[(i,j)]
        
        else: 
            self.energy_cache[i,j] = super().energy(i,j)
            return self.energy_cache[(i,j)]
        
    def best_seam(self, dp=True):
        if (dp):
        #i is column, j is row
        #we have width and height and size
        #remove_seam takes a list of coordinates in a column and removes them and the shifts the rest left
        #energy is what we are trying to minimize so the values in our table should be energy

            T = np.zeros((self.height, self.width)) #dp table the size of the photo
            Last_move = np.zeros((self.height, self.width), dtype=int) #table to store last move so that we can reconstruct the path at the end

            for i in range(self.width):
                T[0,i] = self.energy(i,0) #base cases, T[j,i] is the energy of the pixel at (i,j) plus the minimum of the path of pixels above it

            for j in range(1,self.height):
            #recursion to fill dp table
                for i in range(0, self.width):
                    left_up = T[j-1,i-1] if i-1>=0 else 999999
                    direct_up = T[j-1,i]
                    right_up = T[j-1,i+1] if i+1<self.width else 999999
                    Last_move[j,i] = np.argmin([left_up, direct_up, right_up]) - 1 #-1 for left, 0 for middle, 1 for right
                    T[j,i] = self.energy(i,j) + min(left_up, direct_up, right_up)

            #find min energy in last row because that is the end of the path then we want to work
            # backwards to figure out the min energy path to the top from there

            seam = []
            bottom_row = self.height - 1
            min_index = np.argmin(T[bottom_row]) #returns the column of the min element of the array in the bottom row of the picture
            j = bottom_row 

            while j >= 0: #starting at the bottom row work up to the top row
                seam.append((min_index,j))
                move = Last_move[j,min_index]
                min_index = min_index + move
                j -= 1

            seam.reverse() #flip it around so the top row is the first element in the list
            return seam
        
        else:
            end_col = min(range (self.width), key=lambda i: self.cost(i, self.height-1))
            seam = []
            col = end_col
            for row in range(self.height-1, -1, -1):
                seam.append((col, row))
                if row > 0:
                    moves = [
                        self.cost(col-1, row-1),
                        self.cost(col, row-1),
                        self.cost(col+1, row-1)
                        ]
            col += np.argmin(moves) - 1
            seam.reverse()
            return seam

    def cost(self, i, j):
        # Out of bounds = infinite cost
            if i < 0 or i >= self.width:
                return 9999999
            if j < 0:
                return 9999999
            # Base case
            if j == 0:
                return self.energy(i, 0)
            
            return self.energy(i, j) + min(self.cost (i-1, j-1),self.cost(i,j-1),self.cost (i+1, j-1)) #use smaller pictures
    
   
   