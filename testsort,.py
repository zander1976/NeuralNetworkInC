array = [5, -3, 7, -10, 0, -4, 3, 8, -2, -9]

current_location = 10

while current_location > 0:
    current_location = current_location - 1
    check_location = current_location
    found_location = current_location
    while check_location > 0:
        check_location = check_location - 1
        check_value = array[check_location]
        found_value = array[found_location]
        if found_value < check_value:
            found_location = check_location
    temp = array[found_location]
    array[found_location] = array[current_location]
    array[current_location] = temp

print(array)
