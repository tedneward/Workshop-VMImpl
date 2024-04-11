import sys
from simplevm import VirtualMachine

def main(argc : int, argv : list[str]):
    print("SimpleVM v0.0")
    vm = VirtualMachine()
    # Do something with the vm

if __name__ == '__main__':
    main(sys.argv.count, sys.argv)
