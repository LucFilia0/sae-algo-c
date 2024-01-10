# Importation des modules

from random import *
from numpy import *
from math import *


# Algos de filtres

def filtreLineaire(tab: [int], val: int) -> ([int]):
    """
    :entree: tab [int], val int
    :pre-cond: len(tab)>0
    :sortie: sort [int]
    :post-cond: sort contient tous les indices de 'val' dans tab
    """
    global cpt

    sort = zeros(len(tab), int)
    i = 0
    j = 0
    cpt = cpt + 4
    while i<len(tab) :
        if tab[i] == val :
            sort[j] = i
            j = j+1
            cpt = cpt + 4 # conditon comptee plus bas
        i = i+1
        cpt = cpt + 4
    if j != len(tab)-1:
        sort[j] = -1
        cpt + 5
    return sort

def filtreParDichotomie(tab: [int], val: int) -> ([int]):
    """
    :entree: tab [int], val int
    :pre-cond: len(tab)>0, tab trié
    :sortie: sort [int]
    :post-cond: sort contient tous les indices de 'val' dans tab
    """
    global cpt

    sort = zeros(len(tab), int)
    indice = rechercheDichotomie(tab, val)
    j = 1
    cpt = cpt+5
    if(indice==-1):
        sort[0] = -1
        cpt=cpt+1
    else:
        sort[0] = indice
        curseur_g = indice
        curseur_d = indice
        cpt=cpt+4
        while(tab[curseur_g-1]==val or tab[curseur_d+1]==val):
            if tab[curseur_g-1]==val:
                curseur_g = curseur_g - 1
                sort[j] = curseur_g
                j = j+1
                cpt=cpt+9
            if tab[curseur_d+1]==val:
                curseur_d = curseur_d + 1
                sort[j] = curseur_d
                j = j+1
                cpt=cpt+9
            cpt=cpt+7
    if j!=len(tab)-1 and sort[0]!=-1:
        sort[j] = -1
        cpt=cpt+2
    cpt=cpt+4
    return sort
    


# Algos de tri

def fusion(tab,iDeb,iFin):
    """
    

    Args:
        tab (_type_): _description_
        iDeb (_type_): _description_
        iFin (_type_): _description_
    """
    global cpt
    temp = zeros(iFin - iDeb + 1,'i')
    iMilieu = (iDeb + iFin)//2 
    i = iDeb 
    j = iMilieu + 1 
    k = 0 
    cpt = cpt+8
    while (i <= iMilieu and j <= iFin):
        if (tab[i] < tab[j]): 
            temp[k] = tab[i] 
            i = i + 1 
            cpt = cpt+5
        else:
            temp[k] = tab[j] 
            j = j + 1 
            cpt = cpt+5
        k = k + 1 
        cpt = cpt+6
    cpt = cpt+3
    while (i <= iMilieu): 
        cpt = cpt+8
        temp[k] = tab[i] 
        i = i + 1 
        k=k+1 
    cpt = cpt+1
    while (j <= iFin): 
        temp[k] = tab[j] 
        j = j + 1 
        k = k + 1 
        cpt = cpt+8
    k = 0
    cpt = cpt+2
    while k <= (iFin - iDeb): 
        tab[iDeb + k] = temp[k] 
        k = k + 1 
        cpt = cpt+8
    cpt = cpt+2
        
        
def triFusionRec(tab,i,j):
    """
    """
    global cpt
    cpt = cpt+1
    if i<j:
        m = (i+j)//2
        cpt = cpt+3
        triFusionRec(tab,i,m)
        triFusionRec(tab,m+1,j)
        fusion(tab,i,j)

def triFusion(tab):
    triFusionRec(tab, 0, len(tab)-1)
    

def echanger(tab,a,b):
    global cpt
    tmp=tab[a] 
    tab[a]=tab[b] 
    tab[b]=tmp 
    cpt = cpt+7
    
    
def tabMin(tab,i):
    global cpt
    ind_min=i
    cpt = cpt+1
    while i<len(tab): 
        if tab[i]<tab[ind_min]:
            ind_min=i
            cpt = cpt + 1
        i = i+1 
        cpt = cpt+7
    cpt = cpt+2
    return ind_min


def triSelection(tab):
    global cpt 
    cpt = cpt+2
    i = 0
    ind_min = 0
    while i<len(tab) - 1:
        ind_min = tabMin(tab, i)
        if ind_min != i: 
            echanger(tab, ind_min, i)
        i = i + 1
        cpt = cpt + 3

def triInsertion(tab: [int]):
    i = 1
    global cpt
    while i < len(tab):
        t = i
        trie = False
        while t > 0 and not trie:
            if tab[t] < tab [t - 1]:
                echanger(tab, t, t - 1)
                t = t - 1
                cpt = cpt + 8 + 1 
            else:
                trie = True
                cpt = cpt + 1 
        i = i + 1
        cpt = cpt + 3 + 1 

def tabMax(tab,i):
    global cpt
    ind_max=i
    cpt = cpt+1
    while i<len(tab): 
        if tab[i]>tab[ind_max]:
            ind_max=i
            cpt = cpt+1
        i = i+1
        cpt = cpt+7
    cpt = cpt+2
    return ind_max


def renverser(tab,i):
    global cpt
    j = len(tab)-1
    cpt = cpt + 3
    while i<j:
        echanger(tab,i,j) 
        i = i+1 
        j = j-1
        cpt = cpt+5
    cpt = cpt+1


def triCrepe(tab):
    global cpt
    i=0
    cpt = cpt + 1
    while i<len(tab):
        ind_max=tabMax(tab,i)
        renverser(tab,ind_max)
        renverser(tab,i)
        i = i+1
        cpt = cpt+2
    renverser(tab,0)

def copier(tab):
    tab2=zeros(len(tab),'i')
    for i in range(len(tab)):
        tab2[i]=tab[i]
    return tab2

# Algos de recherche

def rechercheLinéaire(tab,val):
    """
    Renvoie la 1ere occurrence de val en effectuant une recherche linéaire, -1 sinon

    Args:
        tab ([int]): Tableau non vide d'entiers quelconque
        val (int): Valeur à trouver
    
    Returns:
        int: indice de la 1ere occurrence de val, -1 si elle n'est pas dedans
    """
    global cpt
    i = 0
    i_val = -1
    cpt = cpt + 2 
    while i<len(tab) and i_val<0 :
        if tab[i] == val: 
            i_val = i 
            cpt = cpt+1
        i = i+1 
        cpt = cpt+9
    cpt = cpt+2
    return i_val



def rechercheDichotomie(tab: [int], val: int) -> (int):
    """
    Renvoie l'indice d'une des occurrences de val si val est dans le tableau, -1 sinon en effectuant une recherche par Dichotomie

    Args:
        tab ([int]): Tableau non vide d'entiers trié par ordre croissant
        val (int): Valeur à trouver

    Returns:
        int: 1er Indice de val trouvé (pas nécessairement sa 1ere occurrence )
    """
    global cpt
    i = 0
    j = len(tab) - 1
    i_val = -1
    cpt = cpt + 5 # 5 opérations élémentaires avant la boucle
    while i<=j and i_val<0: # 3 comparaisons
        m = (i+j)//2 # 1 affections, 2 opérations
        cpt = cpt + 8
        if tab[m]<val: # 1 requête, 1 comparaison
            i = m+1 # 1 affectation et une opération
            cpt = cpt+2
        else:
            cpt = cpt+2
            if tab[m]>val: # 1 requête, 1 comparaison
                j = m-1 # 1 affectation et une opération
                cpt = cpt+2
            else:
                i_val = m # 1 affectation
                cpt = cpt+1
    cpt = cpt + 3 # 3 comparaisons en sortie de boucle
    return i_val


def rechercheBalayage(tab, val):
    """
    Renvoie l'indice d'une des occurrences de val si val est dans le tableau, -1 sinon en effectuant une recherche par Balayage.
    S'occupe de faire le 1er appel à la fonction rechercheBalayageRec.

    Args:
        tab ([int]): Tableau non vide d'entiers trié par ordre croissant
        val (int): Valeur à trouver

    Returns:
        int: 1er Indice de val trouvé (pas nécessairement sa 1ere occurrence )
    """
    global cpt
    pas = (len(tab)-1)//4
    cpt = cpt + 5
    iVal = rechercheBalayageRec(tab,val,pas, 0,len(tab)-1)
    return iVal

def getIndice(iFin, i, j, pas):
    """
    Renvoie le prochaine indice à traiter pour la fonction rechercheBalayageRec

    Args:
        iFin (int): Indice maximum possible
        i (int): Indice actuel
        j (int): Nombre de tours de boucle effectué
        pas (int): Distance parcourue dans le tableau à chaque tours de boucle

    Returns:
        int: Nouvelle valeur de i
    """
    global cpt
    cpt = cpt + 1
    if j < 3:
        cpt = cpt + 2
        i =  i + pas
    else:
        cpt = cpt + 1
        i = iFin
    return i
        
 
def rechercheBalayageRec(tab, val, pas, iDeb, iFin):
    """
    Renvoie l'indice de val dans le tableau récursivement, -1 si il n'y est pas

    Args:
        tab ([int]): Tableau dans lequel on effectue la recherche
        val (int): Valeur à chercher
        pas (int): Distance parcourue entre 2 recherches
        iDeb (int): Indice minimum à parcourir
        iFin (int): Indice maximum à parcourir

    Returns:
        iVal (int): -1 si val n'est pas le tableau, son indice sinon.
    """
    global cpt
    i = iDeb
    j = 0
    cpt = cpt + 3
    iVal = -1
    if pas == 1:
        while i <= iFin and iVal < 0:
            cpt = cpt + 3
            if tab[i] == val:
                iVal = i
            i = i + 1
            cpt = cpt + 2
        cpt = cpt + 1
        return iVal
    else:
        while j < 4:
            cpt = cpt + 4
            if tab[getIndice(iFin, i, j, pas)] < val:
                cpt = cpt + 2
                i = getIndice(iFin, i, j, pas)
            else:
                iFin = getIndice(iFin, i, j, pas)
                pas = pas//4
                if pas == 0:
                    cpt = cpt + 1
                    pas = 1
                cpt = cpt + 8
                iVal = rechercheBalayageRec(tab, val, pas, i, iFin)
                j = 3
            j = j + 1
            cpt = cpt + 2
        cpt = cpt + 1
        return iVal
        
# Algos heures et retards

def echange_suivant(tab,indice):
    tmp = tab[indice+1]
    tab[indice+1] = tab[indice]
    tab[indice] = tmp

def decalerJusqua(tab,indiceDebut,indiceFin):
    global cpt
    temp = tab[indiceDebut]
    i = indiceDebut
    
    cpt = cpt + 4
    while i < indiceFin:
        tab[i] = tab[i+1]
        i = i + 1
        
        cpt = cpt + 6
    tab[indiceFin] = temp
    cpt = cpt +  4

def ecartHeures(h1,h2):
    """
    Renvoie l'écart en minutes entre les 2 heures
    Il sera négatif si h2 > h1

    Args:
        h1 (int): Stockée sous la forme hhmm (1205 = 12h05), 0 <= h1 < 2400
        h2 (int): Stockée sous la forme hhmm (1205 = 12h05), 0 <= h2 < 2400

    Returns:
        int: écart en minutes entre les 2.
    """
    global cpt 
    heureEcart = h1//100 - h2//100
    minuteEcart = h1%100 - h2%100
    
    cpt = cpt + 9
    if minuteEcart < 0 :
        minuteEcart = minuteEcart + 60
        heureEcart = heureEcart - 1
        
        cpt = cpt + 4
    
    return heureEcart*60 + minuteEcart
    
def ajoutHeure(heure1, val):
    """
    Ajoute val minutes à l'heure

    Args:
        heure1 (int): Stockée sous la forme hhmm (1205 = 12h05), 0 <= heure1 < 2400
        val (int): Nombre de minutes à ajouter (ici 90 = 1h30)

    Returns:
        int: Heure après que val minutes soient passées (l'appel ajoutHeure(1205,90) renvoie 1335)
    """
    global cpt
    heure = heure1//100
    minute = heure1%100
    cpt = cpt + 4
    
    minute = minute + val
    heure = heure + minute//60  
    minute = minute%60
    cpt = cpt + 7
    
    cpt = cpt + 2
    return heure*100 + minute
        


def ajoutRetard(tab, indiceVolRetarde, tpsRetard):
    """
    Retarde un vol de tpsRetard minutes de telle sorte à ce que:
        - Il ait au maximum 60 minutes de retard
        - Il y ait 5 minutes d'écart entre chaque vol
        - Le retard soit le plus bas possible
        - La liste reste triée après usage de la fonction
    Si le vol n'a pas pu être retardé en respectant ces consignes, le vol est annulé:
        - Son heure est mise à -1
        - Il est déplacé à la fin du tableau

    Args:
        tab ([int]): Tableau d'heures représentant la liste de vols, triée par ordre croissant
        indiceVolRetarde (int): Indice du vol retardé dans le tableau d'heures
        tpsRetard (int): Retard en minutes à appliquer au vol

    Returns:
        int: Retard appliqué au vol par la fonction, -1 si il est annulé
    """
    global cpt
    
    cpt = cpt + 5
    heureMin = ajoutHeure(tab[indiceVolRetarde], tpsRetard)
    heureMax = ajoutHeure(tab[indiceVolRetarde], 60)
    if heureMax > 2200:
        cpt = cpt + 1
        heureMax = 2200
    
    cpt = cpt + 6
    retardAccumule = tpsRetard
    indiceVol = indiceVolRetarde
    place = False
    if indiceVolRetarde == len(tab) - 1:
        if tpsRetard <=60:
            tab[indiceVolRetarde] = heureMin
            return tpsRetard
        else:
            tab[indiceVolRetarde] = -1
            return -1
            
        
    while indiceVol + 1 < len(tab) and tab[indiceVol+1] < heureMin:
        indiceVol = indiceVol + 1
        cpt = cpt + 9
        
    heureActuelle = heureMin
    cpt = cpt + 8

    while not place and retardAccumule <= 60 and heureActuelle <= heureMax:
        cpt = cpt + 6
        if indiceVol > indiceVolRetarde :
            cpt = cpt + 3
            ecart1 = ecartHeures(heureActuelle, tab[indiceVol])
            cpt = cpt + 1
            if ecart1 >= 5:
                cpt = cpt + 1
                place = True
        
        cpt = cpt + 3
        if indiceVol + 1 < len(tab) :
            cpt = cpt + 5
            ecart2 = ecartHeures(tab[indiceVol + 1], heureActuelle)
            if ecart2 >= 5:
                cpt = cpt + 1
                if indiceVol > indiceVolRetarde:
                    cpt = cpt + 2   
                    if ecart1 >= 5:
                        place = True
                    else:
                        place = False
            else:
                cpt = cpt + 1
                place = False

        cpt = cpt + 1
        if not place :
            cpt = cpt + 3
            if indiceVol + 1 < len(tab):
                cpt = cpt + 1
                if ecart2 == 0 :
                    indiceVol = indiceVol + 1
                    retardAccumule = retardAccumule + 5
                    heureActuelle = ajoutHeure(heureActuelle, 5)
                    cpt = cpt + 6
                    
                else:
                    retardAccumule = retardAccumule + ecart2
                    heureActuelle = ajoutHeure(heureActuelle, ecart2)
                    cpt = cpt + 4
            
            else:
                retardAccumule = retardAccumule + 1
                heureActuelle = ajoutHeure(heureActuelle, 1)
                cpt = cpt + 4

    cpt = cpt + 6
    
    if place:
        tab[indiceVolRetarde] = heureActuelle
        decalerJusqua(tab, indiceVolRetarde, indiceVol)
        cpt = cpt + 3
    
    else:
        tab[indiceVolRetarde] = -1
        retardAccumule = -1
        decalerJusqua(tab, indiceVolRetarde, len(tab)-1)
        cpt = cpt + 6

    return retardAccumule

# Fonction de test  
    
def tabValide(tab):
    i = 1
    while i < len(tab):
        ecart = ecartHeures(tab[i],tab[i-1])
        if (ecart < 5 and ecart > -5) or (tab[i] < tab[i-1] and tab[i]!=-1) :
            return False
        i = i+1
    return True

def minToH(minute):
    heure = minute//60
    minute = minute%60
    return heure*100 + minute

def create_tab_heure(taille, stepMax, heureDebut):
    tab=zeros(taille,'i')
    tab[0] = minToH(heureDebut)
    i = 1
    while i<len(tab):
        tab[i] = ajoutHeure(tab[i-1],randint(5,stepMax))
        i=i+1
    return tab

def entreeUtilisateur(str,min,max):
    ans = 0
    while ans < min or ans > max:
        ans = int(input(str))
        if ans < min or ans > max:
            print(f"Saissez une valeur entre {min} et {max}")
    return ans
            
    
def test():
    global cpt
    cpt = 0
    done = False
    conserver = 2
    tabTaille = [10,50,200]
    tabTailleRetard = [10,30,64]
    while not done:
        if conserver//2 > 0:
            ans = entreeUtilisateur("Quels Algorithmes souhaitez vous tester ?\n1- Recherches\n2- Filtres\n3- Tris\n4- Ajout de retard\n5- Quitter\n=> ",1,5)

        if ans == 1:
            choix = entreeUtilisateur("Quelle recherche voulez vous tester ?\n1- Linéaire\n2- Dichotomie\n3- Balayage\n=> ", 1, 3)
            if conserver > 0:
                taille = tabTaille[entreeUtilisateur(f"Quelle taille de tableau souhaitez vous utiliser ?\n1- Petit : {tabTaille[0]} valeurs\n2- Moyen : {tabTaille[1]} valeurs\n3- Grand : {tabTaille[2]} valeurs\n=> ",1,3) - 1]
                tab = array([randint(0,taille) for i in range(taille)],'i')
            print(tab)
            val = int(input("Rentrez la valeur que vous souhaitez chercher\n=> "))
            if choix == 1:
                print(f"Indice de la valeur : {rechercheLinéaire(tab, val)}, Nombre d'opérations : {cpt}")
            else:
                tri = entreeUtilisateur("Inclure le tri dans le décompte des opérations (le tri fusion sera utilisé par défaut) ?\n1- Oui\n2- Non\n=> ", 1, 2)
                triFusion(tab)
                if tri == 2:
                    cpt = 0
            if choix == 2:
                print(f"Indice de la valeur : {rechercheDichotomie(tab, val)}, Nombre d'opérations : {cpt}")
            if choix == 3:
                print(f"Indice de la valeur : {rechercheBalayage(tab, val)}, Nombre d'opérations : {cpt}")
            cpt = 0
            conserver = (entreeUtilisateur("Souhaitez refaire des tests sur le même tableau ?\n1 - Oui\n2- Non\n=> ", 1, 2)-1)*2
            
        if ans == 2:
            choix = entreeUtilisateur("Quelle filtre voulez vous appliquer ?\n1- Linéaire\n2- Dichotomie\n=> ", 1, 2)
            if conserver > 0:
                taille = tabTaille[entreeUtilisateur(f"Quelle taille de tableau souhaitez vous utiliser ?\n1- Petit : {tabTaille[0]} valeurs\n2- Moyen : {tabTaille[1]} valeurs\n3- Grand : {tabTaille[2]} valeurs\n=> ",1,3) - 1]
                tab = array([randint(0,taille) for i in range(taille)],'i')
                
            print(tab)
            val = int(input("Rentrez la valeur que vous souhaitez chercher\n=> "))
            
            if choix == 1:
                print(f"Indice de la valeur : {filtreLineaire(tab, val)}, Nombre d'opérations : {cpt}")
            
            else:
                tri = entreeUtilisateur("Inclure le tri dans le décompte des opérations (le tri fusion sera utilisé par défaut) ?\n1- Oui\n2- Non\n=> ", 1, 2)
                triFusion(tab)
                if tri == 2:
                    cpt = 0
                print(f"Indice de la valeur : {filtreParDichotomie(tab, val)}, Nombre d'opérations : {cpt}")
            cpt = 0
            conserver = (entreeUtilisateur("Souhaitez refaire des tests sur le même tableau ?\n1 - Oui\n2- Non\n=> ", 1, 2)-1)*2
        
        
        if ans == 3:
            choix = entreeUtilisateur("Quel tri voulez vous tester ?\n1- Sélection\n2- Insertion\n3- Crêpe\n4- Fusion\n=> ", 1, 4)
            if conserver > 0:
                taille = tabTaille[entreeUtilisateur(f"Quelle taille de tableau souhaitez vous utiliser ?\n1- Petit : {tabTaille[0]} valeurs\n2- Moyen : {tabTaille[1]} valeurs\n3- Grand : {tabTaille[2]} valeurs\n=> ",1,3) - 1]
                tab = array([randint(0,taille) for i in range(taille)],'i')
                copyTab = copier(tab)
                
            else:
                tab = copyTab
            
            print(tab)
            if choix == 1:
                triSelection(tab)
            if choix == 2:
                triInsertion(tab)
            if choix == 3:
                triCrepe(tab)
            if choix ==4:
                triFusion(tab)
            print(tab)
            print(f"Nombre d'opérations : {cpt}")
            conserver = (entreeUtilisateur("Souhaitez refaire des tests sur le même tableau ?\n1 - Oui\n2- Non\n=> ", 1, 2)-1)*2

        if ans == 4:
            if conserver == 2:
                taille = tabTailleRetard[entreeUtilisateur(f"Quelle taille de tableau souhaitez vous utiliser ?\n1- Petit : {tabTailleRetard[0]} valeurs\n2- Moyen : {tabTailleRetard[1]} valeurs\n3- Grand : {tabTailleRetard[2]} valeurs\n=> ",1,3) - 1]
                if taille == tabTailleRetard[0]:
                    tab = create_tab_heure(taille, 60, randint(360,720))
                elif taille == tabTailleRetard[1]:
                    tab = create_tab_heure(taille, 30, randint(360,540))
                else:
                    tab = create_tab_heure(taille, 15, 360)
                copyTab = copier(tab)
            
            if conserver == 1:
                tab = copier(copyTab)
             
            print(tab)   
            indiceVol = entreeUtilisateur("Saisissez l'indice du vol que vous voulez retarder\n =>", 1, taille-1)
            retard = entreeUtilisateur("Rentrez le retard que vous voulez appliquer au vol\n =>", 1, 60)
            retard = ajoutRetard(tab, indiceVol, retard)
            print(f"Avant : {copyTab}")
            print(f"Après : {tab}")
            if retard >= 0:
                print(f"Le vol a été retardé de {retard} minutes.\nNombre d'opérations : {cpt}")
            else:
                print("Le vol n'a pas pu être placé et a été annulé")
            
               
            conserver = entreeUtilisateur("Souhaitez refaire des tests sur le même tableau ?\n"+
                                          "1- Conserver le tableau modifié par la fonction\n"+
                                          "2- Revenir au tableau avant les modifications\n"+
                                          "3- Non\n=> ", 1, 3) -1
                
        if ans == 5:
            print("Merci de corriger notre SAE, on vous aime")
            done = True
            
            
# Tests

cpt = 0
test()
            
