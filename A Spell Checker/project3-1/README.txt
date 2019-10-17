The input and output, in detail

The program takes input in a particular format and writes its output in particular formats, as well, though the code for this has already been written. Still, you'll need to understand these formats in order to complete your work, so they are described below.

The input

The program reads four lines of input from the standard input (i.e., std::cin), without printing any kind of prompts; it simply waits until each line of input arrives before proceeding.

1.The first line selects a search structure. It can be any of the following:
EMPTY, which specifies an "empty set", a search structure that stores no keys and for which all searches return false. (This is used primarily in performance testing.)
LIST, which specifies an unsorted linked list implementation (which has been provided already).
HASH ZERO, which specifies a hash table implementation using a hash function that always returns zero.
HASH SUM, which specifies a hash table implementation using a hash function that sums the character codes for every character of a word.
HASH PRODUCT, which specifies a hash table implementation using a hash function that includes multiplication by prime numbers in its calculation.
AVL, which specifies an AVL tree.
SKIPLIST, which specifies a skip list.

2.The second line specifies the path to a file that contains the word set (i.e., the set of correctly-specified words). The word set file will be assumed to have one correctly-spelled word on each line.
You'll find a file called wordset.txt in your project directory, which is a large set of English words obtained from an open source wordlist project called wordlist.sourceforge.net (Links to an external site.).
You might also want to create one or more smaller word sets to test with, since the provided word set has over 60,000 words.

3.The third line specifies the path to a file that contains the input text for which you want to check spelling. The file will be tokenized (i.e., broken into words, with punctuation and spaces ignored) and the words will be checked by your WordChecker class.
You'll find a file called biginput.txt in your project directory, which is one very large test case that contains a combination of words that are spelled correctly and incorrectly. This, too, was obtained from the open source wordlist project at wordlist.sourceforge.net (Links to an external site.).
You'll almost certainly want to create one or more smaller test inputs, so you can determine whether your implementations of the various Set<ElementType> class templates and your WordChecker class are correct.

4.The fourth line specifies the format of the output you'd like to see, which allows you to choose between seeing a display of the misspellings and suggestions, or whether you're just interested in seeing how much time the spell-checking process takes. This line needs to say either:
DISPLAY, if you want a display of misspellings and suggestions.
TIME, if you want to see only timing results.
