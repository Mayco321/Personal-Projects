import random

def generate_password():
    restart = "yes"
    while restart == "yes": #makes a loop where it restarts if the user needs a change
        characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_-+=<>?"
    #made a type of list where it has all the characthers on the keyboard
        password_length = int(input("How many characthers would you like to have in your password? : "))
    #asks user how many characthers they want to have and get stored into a variable
        if password_length < 4: #makes sure that it has 4 characthers minimum
            print("Password length should be at least 4.")
            return
    
        selected_characters = random.sample(characters, password_length)
    #makes the characthers and length combine
        generated_password = ''.join(selected_characters)
    #password gets made
        print("Random Password is: " + str(generated_password))
    #makes user check their password
        resp = input("What is Your generated password?: ")
        if resp == str(generated_password):
            print("That is Correct!")
        elif resp != str(generated_password):
            print("You have been locked from entering!")
            return
            
        password = str(generated_password)
        user = input("Password: ")#takes them to a login
        if user != str(password): #if incorrect password it stops and prints
            print("UnSuccessful Login!")
            return
        elif user == str(password): #success in password login and finishes
            print("Successful Login!")
        #asks the user if they would like to reset
        restart = input("Would you like to reset password? (Yes or No): ")
        if restart == "no": #if no sudden changes needed print confirmation
            print("Password Confirmed.")
generate_password()# created my function