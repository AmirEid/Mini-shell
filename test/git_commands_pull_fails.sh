Quando INIZIAMO(per copiare le modifiche)
git pull
if (pull not working)
    git stash  (metto da parte momentaneamente i miei file)
    git pull (prendere dal branch remoto (git branch))
    FIX CONFLICTS
    git stash pop (rimetto i miei file che avevo messo da parte con git stash)
git merge
if (ci sono conflitti)
    solve all of them in editor(the one you have to fix have a red dot)