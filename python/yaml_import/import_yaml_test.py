"""
Gabriel Staples
14 Apr. 2020 

Do some yaml file importing to learn how yaml configuration files work.

Run command:
    python3 import_yaml_test.py
- OR (if in the root dir of this repo):
    python3 python/yaml_import/import_yaml_test.py 

References:
1. https://rollout.io/blog/yaml-tutorial-everything-you-need-get-started/
2. PyYAML documentation (scroll down to near the very bottom to see the full reference 
   documentation for all functions): https://pyyaml.org/wiki/PyYAMLDocumentation
"""

import os
import yaml

if __name__ == '__main__':

    # Obtain the path to the directory this file is contained in
    # See: https://stackoverflow.com/questions/5137497/find-current-directory-and-files-directory/5137509#5137509
    dir_path = os.path.dirname(os.path.realpath(__file__))
    print("Directory this Python file is in = \"{}\"\n".format(dir_path))

    print("====================\n"
          "1ST YAML FILE IMPORT\n"
          "====================\n")
    # Open 1st yaml config file
    stream = open("{}/my_config1.yaml".format(dir_path), 'r')
    dictionary = yaml.load(stream)
    # print manually
    for key, value in dictionary.items():
        print(key + " : " + str(value))
    # print automagically
    print()
    print(yaml.dump(dictionary))

    print("====================\n"
          "2ND YAML FILE IMPORT\n"
          "====================\n")
    # Open 2nd yaml config file & update the dictionary
    stream = open("{}/my_config2.yaml".format(dir_path), 'r')
    dictionary.update(yaml.load(stream))
    # print manually
    for key, value in dictionary.items():
        print(key + " : " + str(value))
    # print automagically
    print()
    print(yaml.dump(dictionary))

"""
SAMPLE OUTPUT:


$ python3 python/yaml_import/import_yaml_test.py 
Directory this Python file is in = "/home/gabriel/GS/dev/eRCaGuy_hello_world/python/yaml_import"

====================
1ST YAML FILE IMPORT
====================

doe : a deer, a female deer
ray : a drop of golden sun
pi : 3.14159
xmas1 : True
xmas2 : True
xmas3 : True
xmas4 : True
xmas5 : True
xmas6 : True
xmas7 : True
xmas8 : tRue
french-hens : 3
calling-birds : ['huey', 'dewey', 'louie', 'fred']
xmas-fifth-day : {'calling-birds': 'four', 'french-hens': 3, 'golden-rings': 5, 'partridges': {'count': 1, 'location': 'a pear tree'}, 'turtle-doves': 'two'}
another-list : ['hey', 'there', 'how', 'are', 'you doing', 'today?']

another-list: [hey, there, how, are, you doing, 'today?']
calling-birds: [huey, dewey, louie, fred]
doe: a deer, a female deer
french-hens: 3
pi: 3.14159
ray: a drop of golden sun
xmas-fifth-day:
  calling-birds: four
  french-hens: 3
  golden-rings: 5
  partridges: {count: 1, location: a pear tree}
  turtle-doves: two
xmas1: true
xmas2: true
xmas3: true
xmas4: true
xmas5: true
xmas6: true
xmas7: true
xmas8: tRue

====================
2ND YAML FILE IMPORT
====================

doe : a deer, a female deer
ray : hello there
pi : [23.7, 87.12]
xmas1 : True
xmas2 : True
xmas3 : True
xmas4 : True
xmas5 : True
xmas6 : True
xmas7 : True
xmas8 : tRue
french-hens : 3
calling-birds : ['huey', 'dewey', 'louie', 'fred']
xmas-fifth-day : {'partridges': {'color': 'green'}}
another-list : ['it is nice', 'to meet you.']

another-list: [it is nice, to meet you.]
calling-birds: [huey, dewey, louie, fred]
doe: a deer, a female deer
french-hens: 3
pi: [23.7, 87.12]
ray: hello there
xmas-fifth-day:
  partridges: {color: green}
xmas1: true
xmas2: true
xmas3: true
xmas4: true
xmas5: true
xmas6: true
xmas7: true
xmas8: tRue


"""