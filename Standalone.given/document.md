# Documentation pour les sytèmes embarquées

MBR :
Est un secteur de démarrage qui contient des données persistante :

- Informations sur l'organization des partitions logiques contenant les systèmes de fichiers. (Table de partitions).
- Informations sur l'organization des partitions logiques contenant les systèmes de fichiers. (Table de partitions).
- Code machine qui est chargé dans la ram et executé par le bios et qui permet de charger le system d'exploitation.
- Une signature appelée aussi 'boot sector signature' qui permet au bios de s'assurer qu'il y a un boot loader qui peut être exécuter en toute sécurité.

Le bios charge le code d'amroçage à l'adresse memoire 0X7COO et l'executer pour ensuite donner la main au chargeur d'amorcage après la lecture de la valeur 0xAA55 ( 2 octes).

ISA :
Instruction set architecture est un model abstrait pour ordinateur.
definie le comportement du machine code de manière que ca ne soit pas dépendant des characteristiques de l'implementation, ce qui garantie une compatibilité entre les different implementations et permet d'autoriser plusieurs implementations qui sont different en performance,taille physique...

ABI: Application binary interface

Est une interface entre deux modules/programmes binaire, generalement un de ces deux modules et un système d'exploitation ou une bibliothèque et le deuxième programme est un programme lancer par l'utilisateur.

Definit la maniere d'acceder a une structure de données en code machine de sourte que le code source marchera sur tout les systemes supportant cette API.
Définit les convention d'appel des fonctions, le role des registres généraux.

ABI est souvent exposé sous forme de VDSO (Virtual Dynamic Shared Object), est une bibliothèque partagée qui permet à l'application dans l'espace utilisateur d'effectuer certaines actions du noyau sans autant de surcharge qu'un appel système.

# Les bases du MakeFile

Compilation, test, suppression de fichiers...

Son Avantage par rapport a un fichier script est qu'il se lance que si la cible est à jour et ne s'execute donc que si c'est nécessaire.

make : lance la première cible definie dans le makefile

make cible : lance la cible preciser

make -f autreficher : execute les regles de 'autre_fichier'

make -n : dry run (affiche les commandes seulement)

Syntaxe d'une règle MakeFile

cible: dépendences
    commandes

- les lignes de commandes commencent par une tabulation

- Cible c'est soit un identificant soit un fichier à generer (fichier .s)

- Dépendances est composé d’identifiants et/ou de noms de fichiers

- Commandes correspond aux actions à effectuer

Cibles Standard :
• all:  compile l’ensemble du programme, Les dépendances correspondent à l’ensemble des fichiers à produire, Doit être la règle par défaut

• install : compile le programme et copie les exécutables/librairies à l’endroit approprié

• clean : La commande associée supprime tous les fichiers intermédiaires, Pas de dépendances

Utilisation de variables
• Définition: NOM=valeur
• Utilisation: $(NOM) ou ${NOM}
• Variables imbriquées: VAR= $(VAR1) $(VAR2)
Variables standards en C/C++
• CC: désigne le compilateur utilisé
• CFLAGS: regroupe les options de compilation
• LDFLAGS: regroupe les options d’édition de liens
• EXEC ou TARGET: regroupe les exécutables

Variables automatiques
• $@: le nom de la cible
• $<: le nom de la première dépendance
• $?: le nom de toutes les dépendances qui sont plus récentes que la cible.
• $^: le nom de toutes les dépendances
• $*: Le nom du pattern matchant la cible dans un pattern statique

Sources : Wikipedia pour les définitions, youtube pour certain details, https://tropars.github.io/teaching/#devops pour makefile