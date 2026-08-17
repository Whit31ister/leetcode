# Example of Linear Big(O)

def listreturn(list):
    for i in list:
        if i == 2:
            return True
        else:
            pass
    return False


list = [3,4,5,6,1,3,6]

if listreturn(list):
    print("List containes 2")
else:
    print("List does not contain 2")


