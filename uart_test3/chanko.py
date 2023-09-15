import serial
import time



#pip uninstall serial
#pip install pyserial
#不要使用try 错误不显示
s =  serial.Serial("COM6",9600,timeout = 5)
##try:
print(s.isOpen())


while(1):
##        write to arduino 
    s1 = input("输入:（exit)")
    t = s1 + '\n'
    print(t)
    
##    len = s.write(t.encode("utf-8"))
    len = s.write(235 )
    print("send len:",len)

    r1 = ''
    for i in range(1):
        r1 +=  s.read().decode("utf-8")
    print("receve data :",r1)

##    time.sleep(100)
##      read from arduino
##        r1 = ''
##        for i in range(20):
##            s1 += uart.read().decode("utf-8")
##        print("receve data:",s1)        
##        
    
##        if(s == "exit"):
##            print("to exit....")
##            break

        

##except :
s.close()
pass


##        str = ''
##        for i in range(len):
##            str += uart.read().decode("utf-8")
##        print("receve data:",str)
