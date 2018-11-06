import struct

def get_pgm_token(f):
    ''' this function takes file object
    and returns magic number, width, height, color'''





if __name__ == '__main__':
    import sys.argv
    script, image_file = argv
    pgm_tokens = ()
    with open(image_file) as f:
        try :
            if f:
                pgm_tokens = get_pgm_token(f)
        except :
