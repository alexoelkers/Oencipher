"""a simplet script to read a file and encipher it"""

KEYLENGTH = 64  # length of keys in bits

def xor(a, b):
    return (a and not b) or (not a and b)

def feistel_cipher(plain_text, key_schedule, round_function):
    left_text = plain_text[:KEYLENGTH/2]
    right_text = plain_text[KEYLENGTH/2:]

    for key in key_schedule:
        left_text = right_text
        right_text = xor(left_text, round_function(right_text, key))

    return left_text + right_text


if __name__ == "__main__":
    with open("test.txt", "rb", buffering=8) as file:
        for line in file:
            print(line)        