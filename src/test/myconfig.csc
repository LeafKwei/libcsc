; This is a sample of csc(Command-Style Configuration)
; Note if you want to use this file to test libcsc on linux, please use 'dos2unix' convert CR-LF to LF

action "genidx"
action "detail"

player = "Smith"
isMale = false

custom::                  ; scope
    tom::                   ; child scope
        action "genidx"
        name = "tom"                                ; string
        age = 3                                           ; number.
        height = 171.5                               ; number.
        weight = 0x3F                                ; number.
        cash = -100                                    ; number with sign
        cost  = +114.5                                ; number with sign
        isHappy = true                               ; bool.
        friend = {"jerry", "jimi", "cherry"}    ; array. All elements in array must be a same type.
        score = {0x1873, 0xFF7, 9883, 100}
        chovice = {true, false, true, true}
    ::tom
    
    ; We can use '\' to escape symbol in the string to avoid it to be recognized.
    school = "The university for \"cat\" and \"mouse\""

::custom

another_custom::
    sth::
    ::sth
::another_custom

