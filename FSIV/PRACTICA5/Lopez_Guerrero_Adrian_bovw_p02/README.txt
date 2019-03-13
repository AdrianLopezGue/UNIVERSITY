# FSIV-FINAL-PROJECT-PART-1

HOW TO COMPILE:

1.- execute "cmake CMakeList.txt"
2.- execute "make"

HOW TO RUN THE PROGRAMS:

train_bow:

1.- execute "train_bow [arguments]"
2.- Done!

Example: ./train_bovw -t 0 -s 800 -v 100 -k 200 -a 0 -e 4 -c ../data/02_ObjectCategories_conf.txt


test_bow:

1.- execute "test_bovw --img <input_image> --classifier <path_classifier> --dict <path_dictionary> --config_file <path_classes_config>"
2.- Done!

Example: ./test_bovw -i combo.jpg -x SURF_NTHRES800_NTRAIN100_CATEGORIES=2_CLASS_SVM=4_classifier.yml -d SURF_NTHRES800_NTRAIN100_CATEGORIES=2_CLASS_SVM=4_dictionary.yml -t 0 -a 1
