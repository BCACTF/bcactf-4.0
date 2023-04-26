from time import sleep
import sys

def setup():
    print("bcactf{h4rdW@r3_r3$Et?_!1y8fbr4eu}")

def main():
    pins = [{"val":0,"type":None} for _ in range(14)]
    reset = {"val":0,"type":"INPUT"}
    welcome = """
    hello. this is my arduino simulator (only digital pins supported). type one of the following commands to do stuff.
    help - shows this message
    exit - turns off the board
    press (button) - presses a button.
        valid options are 'RESET' and digital pins 0-13 (if they are set to INPUTS)
    release (button) - releases a button.
        valid options are 'RESET' and digital pins 0-13 (if they are set to INPUTS)
    set (pin) (mode) - sets a pin to a mode.
        valid options for pins are digital pins 0-13.
        valid options for mode are 'INPUT' and 'OUTPUT'
    read (pin) - reads an INPUT or OUTPUT pin.
        valid options for pins are digital pins 0-13.
    write (pin) (value) - writes a value to an OUTPUT pin.
        valid options for pins are digital pins 0-13.
        valid options for value are 'HIGH' and 'LOW'
    print (message) - prints a message to the Serial Monitor.
        message can be any string less than 1024 characters.
    """
    print(welcome)
    
    command = ""
    while command != "exit":
        try:
            command = input(">>> Enter a command:\n")
            if command == "help":
                print(welcome)
                
            elif command.startswith("press"):
                button = command.split(" ")[1]
                if button == "RESET":
                    print("(resetting...)")
                    sleep(1)
                    continue
                pin = int(button)
                if pin < 0 or pin > 13:
                    print("(invalid pin)")
                    continue
                if pins[pin]["type"] == "INPUT":
                    pins[pin]["val"] = 1
                    print(f"(turned on pin {pin})")
                else:
                    print("not an input pin")

            elif command.startswith("release"):
                button = command.split(" ")[1]
                if button == "RESET" and reset["val"] == 1:
                    print("(successfully reset)")
                    setup()
                    break
                pin = int(button)
                if pin < 0 or pin > 13:
                    print("(invalid pin)")
                    continue
                if pins[pin]["type"] == "INPUT":
                    pins[pin] = 0
                    print(f"(turned off pin {pin})")
            
            elif command.startswith("set"):
                pin = int(command.split(" ")[1])
                mode = command.split(" ")[2]
                if pin < 0 or pin > 13:
                    print("(invalid pin)")
                    continue
                if mode in ["INPUT","OUTPUT"]:
                    pins[pin]["type"] = mode
                else:
                    print("(invalid mode)")

            elif command.startswith("read"):
                pin = int(command.split(" ")[1])

                if pin in range(14) and (pins[pin]["type"] == "INPUT" or pins[pin]["type"] == "OUTPUT"):
                    print(f"(pin {pin} is {pins[pin]['val']})")
                else:
                    print("(invalid pin)")

            elif command.startswith("write"):
                pin = int(command.split(" ")[1])
                if pin < 0 or pin > 13:
                    print("(invalid pin)")
                    continue
                value = command.split(" ")[2]
                if pins[pin]["type"] == "OUTPUT":
                    if value == "HIGH":
                        pins[pin]["val"] = 1
                    elif value == "LOW":
                        pins[pin]["val"] = 0
                    else:
                        print("(invalid value)")
                else:
                    print("(not an output pin)")

            elif command.startswith("print"):
                print(command[6::])
            
            else:
                print("invalid command")
        except Exception as e:
            print("thou hath broken the simulator. please leave at once")
            sys.exit(-1)
    
    print("Exiting Simulator...")
    sleep(1)
    print("Finished")



if __name__ == '__main__':
    main()