#### Pleace, create your oun branch from develop with name according to exel table
    git checkout -b XX-YY_Surname_Name
or

    git branch XX-YY_Surname_Name
    git checkout XX-YY_Surname_Name

#### Create inside folder Lab_XX new folder with the same name as your branch name
    cd Lab_XX
    mkdir XX-YY_Surname_Name
    cd XX-YY_Surname_Name

#### After compliting your task check all changed files
    git status

#### Add and commit changed or untracked files with next commit message
    git add -p
    git commit -m "Lab_X: Description which begins from Verb"

#### Push your changes into remote repository
    git push origin XX-YY_Surname_Name
