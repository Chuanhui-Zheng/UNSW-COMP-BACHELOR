import re
def read_dna(dna_file):
    """
    Read a DNA string from a file.
    the file contains data in the following format:
    A <-> T
    G <-> C
    G <-> C
    C <-> G
    G <-> C
    T <-> A
    Output a list of touples:
    [
        ('A', 'T'),
        ('G', 'C'),
        ('G', 'C'),
        ('C', 'G'),
        ('G', 'C'),
        ('T', 'A'),
    ]
    Where either (or both) elements in the string might be missing:
    <-> T
    G <->
    G <-> C
    <->
    <-> C
    T <-> A
    Output:
    [
        ('', 'T'),
        ('G', ''),
        ('G', 'C'),
        ('', ''),
        ('', 'C'),
        ('T', 'A'),
    ]
    """
    list1 = list()
    file = open(dna_file)
    while True:

        lines = file.readline()

        lines = re.sub('\n', '', lines)
        if lines == '':
            break
        partition = re.split(' <-> ', lines)
        if len(partition) == 0:
            touples = (' ', ' ')
        elif len(partition) == 1:
            if re.search('[A-Z] <->', lines) is not None:
                touples = (partition[0], ' ')
            if re.search(' <-> [A-Z]', lines) is not None:
                touples = (' ', partition[0])
        else:
            touples = (partition[0], partition[1])
        list1.append(touples)
    return list1
    

def is_rna(dna):
    """
    Given DNA in the aforementioned format,
    return the string "DNA" if the data is DNA,
    return the string "RNA" if the data is RNA,
    return the string "Invalid" if the data is neither DNA nor RNA.
    DNA consists of the following bases:
    Adenine  ('A'),
    Thymine  ('T'),
    Guanine  ('G'),
    Cytosine ('C'),
    RNA consists of the following bases:
    Adenine  ('A'),
    Uracil   ('U'),
    Guanine  ('G'),
    Cytosine ('C'),
    The data is DNA if at least 90% of the bases are one of the DNA bases.
    The data is RNA if at least 90% of the bases are one of the RNA bases.
    The data is invalid if more than 10% of the bases are not one of the DNA or RNA bases.
    Empty bases should be ignored.
    """
    count = 0
    count_dna = 0
    count_rna = 0
    for i in dna:
        if (i[0] == 'A' or i[0] == 'T' or i[0] == 'G' or i[0] == 'C') and (i[1] == 'A' or i[1] == 'T' or i[1] == 'G' or i[1] == 'C'):
            count_dna +=  1
        if (i[0] == 'A' or i[0] == 'U' or i[0] == 'G' or i[0] == 'C') and (i[1] == 'A' or i[1] == 'U' or i[1] == 'G' or i[1] == 'C'):
            count_rna += 1
        count += 1
        
    if count_dna > count_rna and count_dna > 0.9 * count:
        return 'DNA'
    if count_rna > count_dna and count_rna > 0.9 * count:
        return 'RNA'
    if count_dna < 0.9 * count or count_rna < 0.9 * count:
        return 'Invalid'


def clean_dna(dna):
    """
    Given DNA in the aforementioned format,
    If the pair is incomplete, ('A', '') or ('', 'G'), ect
    Fill in the missing base with the match base.
    In DNA 'A' matches with 'T', 'G' matches with 'C'
    In RNA 'A' matches with 'U', 'G' matches with 'C'
    If a pair contains an invalid base the pair should be removed.
    Pairs of empty bases should be ignored.
    """
    if is_rna(dna) == 'DNA':
        count = 0
        for i in dna:
            if i[0] == '' and i[1] == '':
                dna.remove(i)
            if i[0] == '' and i[1] == 'A':
                dna[count] = ('T','A')
            if i[0] == 'A' and i[1] == '':
                dna[count] = ('A','T')
            if i[0] == 'T' and i[1] == '':
                dna[count] = ('T','A')
            if i[0] == '' and i[1] == 'T':
                dna[count] = ('A','T')
            if i[0] == '' and i[1] == 'G':
                dna[count] = ('C', 'G')
            if i[0] == 'G' and i[1] == '':
                dna[count] = ('G','C')
            if i[0] == 'C' and i[1] == '':
                dna[count] = ('C', 'G')
            if i[0] == '' and i[1] == 'C':
                dna[count] = ('G','C')
            count += 1
    if is_rna(dna) == 'RNA':
        count = 0
        for i in dna:
            if i[0] == '' and i[1] == '':
                dna.remove(i)
            if i[0] == '' and i[1] == 'A':
                dna[count] = ('U','A')
            if i[0] == 'A' and i[1] == '':
                dna[count] = ('A','U')
            if i[0] == 'U' and i[1] == '':
                dna[count] = ('U','A')
            if i[0] == '' and i[1] == 'U':
                dna[count] = ('A','U')
            if i[0] == '' and i[1] == 'G':
                dna[count] = ('C', 'G')
            if i[0] == 'G' and i[1] == '':
                dna[count] = ('G','C')
            if i[0] == '' and i[1] == 'C':
                dna[count] = ('G', 'C')
            if i[0] == 'C' and i[1] == '':
                dna[count] = ('C','G')
            count += 1
    return dna

def mast_common_base(dna):
    """
    Given DNA in the aforementioned format,
    return the most common first base:
    eg. given:
    A <-> T
    G <-> C
    G <-> C
    C <-> G
    G <-> C
    T <-> A
    The most common first base is 'G'.
    Empty bases should be ignored.
    """
    count_g = 0
    count_a = 0
    count_c = 0
    count_t = 0
    count_u = 0
    for i in dna:
        if i[0] == 'G':
            count_g += 1
        if i[0] == 'A':
            count_a += 1
        if i[0] == 'C':
            count_c += 1
        if i[0] == 'T':
            count_t += 1
        if i[0] == 'U':
            count_u += 1
    max = count_t
    if max < count_a:
        max = count_a
    if max < count_c:
        max = count_c
    if max < count_g:
        max = count_g
    if max < count_u:
        max = count_u
    if max == count_g:
        return "G"
    if max == count_a:
        return "A"
    if max == count_c:
        return "C"
    if max == count_t:
        return "T"
    if max == count_u:
        return "U"

def base_to_name(base):
    """
    Given a base, return the name of the base.
    The base names are:
    Adenine  ('A'),
    Thymine  ('T'),
    Guanine  ('G'),
    Cytosine ('C'),
    Uracil   ('U'),
    return the string "Unknown" if the base isn't one of the above.
    """
    if base == "A":
        return "Adenine"
    if base == "T":
        return "Thymine"
    if base == "G":
        return "Guanine"
    if base == "C":
        return "Cytosine"
    if base == "U":
        return "Uracil"