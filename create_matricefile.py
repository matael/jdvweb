# Initialize the matrix file with a empty matrix

number_of_rows = 60
number_of_cols = 60


file = open("Matrice.JDV",'w')
for i in range(number_of_rows):
    for j in range(number_of_cols):
        file.write('0')
    file.write('\n')
file.close()
