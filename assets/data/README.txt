Read templates and README.txt files when modifying and you don't know what you are doing

ATRC syntax:

Variables
    - Variables are all constants. Redefining one will result in an error
    - Variables need to be defined before inserted into a value
    - Non-special variables cannot start with a asterisk (*)
    - Defining a variable:
        - %var_name%=value

    - Defining a private variable:
        - <%var_name%=value
            - Private variables cannot be accessed by the program

Special variables
    - Two types of special variables, insert and numeral insert
    - Insert:
        - %*%
            - Value can be inserted here by the program
    - Numeral insert
        - %*0%, %*1%, %*2%...
            - With numeral inserts you can define the order the values will be inserted, starting at 0

Blocks
    - Blocks are an array that hold a set of keys
    - Defining a block:
        - [block_name]
Keys
    - Keys are the same as variables, but they can be only accessed through the block.
    - Defining a key:
        - key_name=value

Reserved characters
    - Three types of special characters:
        - ! is a comment
        - & is a whitespace symbol
        - % is for variables
    - If you want to add a reserved character into a value, prefix it with a backslash (\)
    - Block, variable or key names cannot include a reserved character

Example file
    ! ATRC EXAMPLE FILE
    %operating_system%=ms-dos
    [INTRODUCTIONS]
    ! User name inserted at insert
    introduction_1 = Login as %*% into %operating_system%&
    ! Output: "Login as USER into ms-dos "

    ! username at 1 insert, logoff time at 0 insert
    introduction_2=Welcome back %*1%\! You were logged off for %*0% hours.
    ! Output: "Welcome back USER! You were logged off for 0.5 hours."