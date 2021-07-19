# RLpacks

Hello there!

RLpacks is a windows-GUI made with wxWidgets.
This GUI is specifically made for rocket league.

In rocket league, you have training packs that you can use for custom training

This GUI will basically allow you to search for packs- almost like a google search engine.

Additionally there is a way for you to insert your own packs.

# How it works:
## 2 versions
The non_postgreSQL version will have to download this to a textfile before you run the GUI each time, so that the GUI can access the packs
There are two versions to this GUI:
-The first one(non_postgres) is if you don't have postgreSQL on your computer. This works well enough.

There is a postgreSQL database that contains all the packs where the info:
</br>-name</br>
-code</br>
-tags</br>

If you use the postgreSQL version, then you directly access this database.
If you use the non-postgreSQL version, then you will access the "packs.txt" file that is present in the non_postgres folder.

## Searching
Searching for both versions works the same. Like a google search bar- the search terms you look for will be searched for and returned

## Inserting
For the postgreSQL version, inserting a pack is easy.
You will enter all the relevent data and click "insert", which will then send the pack into a database

For the non-postgresSQL version, its the same but instead the GUI will generate a "insert.txt" text with the packs you insert.
I still need to code a method for you to send it to me.

#NB
This is still under developement and I'm continuing to contribute and make it as stable as possible.
