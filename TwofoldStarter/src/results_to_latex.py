import re

# Match one or more digits 
p = re.compile('\d+')
DIR = 'C:\\Users\\alexi_000\\OneDrive\\Documents\\thesis\\code\\crepo\\TwofoldStarter\\Results'
FILE = '\\twofold_2starters_10_40.txt'
file = open(DIR + FILE, "r")
spaceSize = '\;'
comma = ', ' + spaceSize
latexFile = DIR + '\\starters.tex'
output = open(latexFile, "w")
prevOrder = -1
for line in file:
    #print('In line ', line)
    nums = p.findall(line)
    #print(nums)
    order = int(nums[0])
    if(order != prevOrder):
        output.write('\n')
        prevOrder = order
        
    paramSum = 0
    params = []
    i = 1
    latexCode = '$OP('
    #print('order is ', order)
    
    
    while(paramSum != order):
        #print('paramSum is ', paramSum)
        param = int(nums[i])
        paramSum += param
        params.append(param)
        i += 1

    starter = nums[len(params)+1:]
    #print('starter section is ', starter)
    latexCode += str(params[0])
    
    for j in range(1, len(params)):
        latexCode += comma
        latexCode += str(params[j])

    latexCode += '): \:'
    start = 0
    
    for j in range(0, len(params)):
        latexCode += '('
        if(j > 0):
            start += int(params[j-1])

        if(int(starter[start]) == order -1):
            latexCode += '\infty'
        else:
            latexCode += starter[start]
            
        for k in range(1, params[j]):
            vertex = starter[start + k]
            latexCode += comma
            
            if(int(vertex) == order-1):
                latexCode += '\infty'
            else:
                latexCode += vertex

        latexCode += ')'

    latexCode += '$\\\\'
    print(latexCode)
    output.write(latexCode + '\n')
    
            
                       

    
