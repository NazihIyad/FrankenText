In my program i wrote this little story: 
char book[] =
    "The monster screamed! The monster didn't run away. "
    "The monster ate the food! The monster danced! "
    "The monster cried! The monster laughed!";

Output:
    PS C:\Users\nazih\Desktop\Programming C UNI\FrankenText> cd 'c:\Users\nazih\Desktop\Programming C UNI\FrankenText\output'
PS C:\Users\nazih\Desktop\Programming C UNI\FrankenText\output> & .\'main.exe'    
The monster laughed!
PS C:\Users\nazih\Desktop\Programming C UNI\FrankenText\output> cd 'c:\Users\nazih\Desktop\Programming C UNI\FrankenText\output'
PS C:\Users\nazih\Desktop\Programming C UNI\FrankenText\output> & .\'main.exe'
The monster laughed!
PS C:\Users\nazih\Desktop\Programming C UNI\FrankenText\output> cd 'c:\Users\nazih\Desktop\Programming C UNI\FrankenText\output'
PS C:\Users\nazih\Desktop\Programming C UNI\FrankenText\output> & .\'main.exe'
The monster laughed!

Explanation for documentation:
- The program picks a starting word that begins with a capital letter (The).
- Then it prints the “next word” according to the program’s successor table.
- In this simple version, each token only remembers one next word, so the output is always the same.

flowchart:
<img width="84" height="277" alt="image" src="https://github.com/user-attachments/assets/f9f6755f-9b84-4592-85e1-3f89cb2a671f" />
