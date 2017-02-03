# ctlCPU
On a ajoute la possibilité de limiter plusieurs processus a la fois, et de donner en argument les pourcentages d’utilisation alloues a chacun des processus.

La syntaxe est:
./pitCPU -pid pid[1],pid[2],…,pid[n] -pct pct[1],…,pct[n]

Attention il n’y a aucune protection contre un mauvais input. On peut aussi toujours simplement limiter un seul processus sans declarer les options:

./pitCPU pid pct

La version que j’ai envoye tout a l’heure n’était pas fonctionelle, j’ai modifie char **eclaterChaine() de maniere a ce que eclaterChaine()[0] soit un *char contenant le sprintf de nbChaine-1, c’est a dire la stringification de la longueur de l’array retourne.

Khalid a aussi propose d’utiliser une librairie d’interface graphique, soit wxwidgets ou xwindow je crois.
