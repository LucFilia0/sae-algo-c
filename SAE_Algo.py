# Importation des modules

from random import *
from numpy import *
import time


# Algos de filtres

def filtre_lineaire(tab: [int], val: int) -> ([int]):
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

def filtre_par_dichotomie(tab: [int], val: int) -> ([int]):
    """
    :entree: tab [int], val int
    :pre-cond: len(tab)>0, tab trié
    :sortie: sort [int]
    :post-cond: sort contient tous les indices de 'val' dans tab
    """
    global cpt

    sort = zeros(len(tab), int)
    indice = recherche_dichotomie(tab, val)
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
    global cpt
    temp = zeros(iFin - iDeb + 1,'i') # 1
    iMilieu = (iDeb + iFin)//2 # 3
    i = iDeb # 1
    j = iMilieu + 1 # 2
    k = 0 # 1
    cpt = cpt+8
    while (i <= iMilieu and j <= iFin): # 3
        if (tab[i] < tab[j]): # 3
            temp[k] = tab[i] # 3
            i = i + 1 # 2
            cpt = cpt+5
        else:
            temp[k] = tab[j] # 3
            j = j + 1 # 2
            cpt = cpt+5
        k = k + 1 # 2
        cpt = cpt+6
    cpt = cpt+3
    while (i <= iMilieu): # 1
        cpt = cpt+8
        temp[k] = tab[i] # 3
        i = i + 1 # 2
        k=k+1 # 2
    cpt = cpt+1
    while (j <= iFin): # 1
        temp[k] = tab[j] # 3
        j = j + 1 # 2
        k = k + 1 # 2
        cpt = cpt+8
    k = 0
    cpt = cpt+2
    while k <= (iFin - iDeb): # 2
        tab[iDeb + k] = temp[k] # 4
        k = k + 1 # 2
        cpt = cpt+8
    cpt = cpt+2
        
        

def tri_fusion(tab,i,j):
    """
    """
    global cpt
    cpt = cpt+1
    if i<j:
        m = (i+j)//2
        cpt = cpt+3
        tri_fusion(tab,i,m)
        tri_fusion(tab,m+1,j)
        fusion(tab,i,j)

def echanger(tab,a,b):
    global cpt
    tmp=tab[a] # 2
    tab[a]=tab[b] # 3
    tab[b]=tmp # 2
    cpt = cpt+7
    
    
def tab_min(tab,i):
    global cpt
    ind_min=i
    cpt = cpt+1
    while i<len(tab): #2
        if tab[i]<tab[ind_min]: #3
            ind_min=i
            cpt = cpt + 1
        i = i+1 # 2
        cpt = cpt+7
    cpt = cpt+2
    return ind_min


def tri_selection(tab):
    """
    """
    global cpt 
    cpt = cpt+2
    i=0
    ind_min=0
    while i<len(tab)-1:
        ind_min=tab_min(tab,i)
        if ind_min!=i: # 1
            echanger(tab,ind_min,i)
        i = i+1
        cpt = cpt + 3

def tri_insertion(tab: [int]):
    i = 1
    global cpt
    while i < len(tab):
        t = i
        trie = False
        while t > 0 and not trie:
            if tab[t] < tab [t - 1]:
                echanger(tab, t, t-1)
                t = t -1
                cpt = cpt + 8 + 1 #
            else:
                trie = True
                cpt = cpt + 1 #
        i = i + 1
        cpt = cpt + 3 + 1 #

def tab_max(tab,i):
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
    while i<j: # 1
        echanger(tab,i,j) 
        i = i+1 # 2
        j = j-1 # 2
        cpt = cpt+5
    cpt = cpt+1


def tri_crepe(tab):
    global cpt
    i=0
    cpt = cpt + 1
    while i<len(tab): #2
        ind_max=tab_max(tab,i)
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

def recherche_linéaire(tab,val):
    """
    entrée: tab:[int], val:int ;
    pré-cond: None ;
    sortie: i_val,cpt:int ;
    post-cond: i_val vaut l'indice de la 1ere occurrence de la valeur recherchée,
    -1 si il n'est pas dans le tableau
    cpt est le nombre d'opérations élémentaires effectuées ;
    """
    global cpt
    i = 0
    i_val = -1
    cpt = cpt + 2 # 2 opérations élémentaires avant la boucle
    while i<len(tab) and i_val<0 : # 1 requête, 3 comparaisons
        if tab[i] == val: # 1 requêtes et une comparaison
            i_val = i # 1 affectation
            cpt = cpt+1
        i = i+1 # 1 opération et 1 affectation
        cpt = cpt+9
    cpt = cpt+2
    return i_val



def recherche_dichotomie(tab: [int], val: int) -> (int):
    """
    pré-cond: None ;
    sortie: i_val,cpt:int ;
    post-cond: i_val vaut l'indice de la 1ere occurrence de la valeur recherchée,
    -1 si il n'est pas dans le tableau
    cpt est le nombre d'opérations élémentaires effectuées ;
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


def recherche_balayage(tab,val):
    """
    entrée: tab:[int], val:int ;
    pré-cond: None ;
    sortie: i_val,cpt:int ;
    post-cond: i_val vaut l'indice de la 1ere occurrence de la valeur recherchée,
    -1 si il n'est pas dans le tableau
    cpt est le nombre d'opérations élémentaires effectuées ;
    """
    global cpt
    last = 0 # 1
    pas = len(tab)//4 # 3
    cpt = cpt+4
    while last==0: # 1
        if pas==1: # 1
                last=1 # 1
                cpt=cpt+1
        i = 0 #1
        cpt=cpt+2
        while i<len(tab) and tab[i]<val: # 5
            i = i+pas # 2
            cpt = cpt+7
            
        if i<len(tab) and tab[i]==val: #5
               cpt = cpt+5
               return i
        else:
            cpt = cpt+5
            i = i-pas # 2
            pas = pas//4 # 2
            if pas==0: #1
                cpt = cpt+1
                pas=1 #1
            cpt=cpt+5
        cpt=cpt+5
    return -1

def rechercheBalayage2(tab, val):
    global cpt
    pas = len(tab)//4
    return rechercheBalayageRec(tab,val,pas, 0,len(tab)-1, False)

def getIndice(iFin, i, j, pas):
    global cpt
    if j < 3:
        return i + pas
    else:
        return iFin
        
 
def rechercheBalayageRec(tab, val, pas,iDeb, iFin,trouve):
    global cpt
    if pas>0 and not trouve:
        i = iDeb
        j = 0
        while j < 4:
            if tab[i] < val:
                i = getIndice(iFin, i, j, pas)     
            else:
                if tab[i] == val:
                    trouve = True
                    done = True
                    return i
                else:
                    iFin = getIndice(iFin, i, j, pas)
                    if pas == 1:
                        pas = 0
                    else:
                        nvPas = pas//4
                    return rechercheBalayageRec(tab, val, nvPas, i-pas, iFin, trouve)
    else:
        print(trouve)
        if not trouve:
            return -1
                    
                    
                
            
    

# Algos heures et retards

def create_tab_heure(taille,step_max):
    tab=zeros(taille,'i')
    tab[0] = randint(360,700)
    i = 1
    while i<len(tab):
        tab[i] = tab[i-1]+randint(5,step_max)
        i=i+1
    return tab
    
    
    
def afficherTabHeure(tab):
    i = 0
    print("[",end=' ')
    while i < len(tab):
        if tab[i]!=-1:
            print(f"{i}:{heure(tab[i])}",end=' ')
        else:
            print("vol annule",end=' ')
        i = i + 1
    print("]\n")
    
    
    
def heure(minutes):
    h = minutes//60
    min = minutes%60
    return f"{h}h{min}"



def echange_suivant(tab,indice):
    tmp = tab[indice+1]
    tab[indice+1] = tab[indice]
    tab[indice] = tmp


def ecartHeures(h1,h2):
    global cpt 
    heureEcart = h1//100 - h2//100
    minuteEcart = h1%100 - h2%100
    
    cpt = cpt + 9
    if minuteEcart < 0 :
        minuteEcart = minuteEcart + 60
        heureEcart = heureEcart - 1
        
        cpt = cpt + 4
    
    return heureEcart*60 + minuteEcart
        

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
    
def ajoutHeure(heure1, val):
    heure = heure1//100
    minute = heure1%100
    
    minute = minute+val
    
    while minute >= 60:
        heure = heure + 1
        minute = minute - 60
        
    while minute < 0 :
        heure = heure -1
        minute = minute + 60
        
    return heure*100+minute
        


def ajoutRetard(tab, indiceVolRetarde, tpsRetard):
    global cpt
    
    heureMin = ajoutHeure(tab[indiceVolRetarde], tpsRetard)
    heureMax = ajoutHeure(tab[indiceVolRetarde], 60)
    if heureMax > 2200:
        heureMax = 2200
    
    retardAccumule = tpsRetard
    indiceVol = indiceVolRetarde
    place = False
    
    
    if len(tab) > 1:
        while indiceVol + 1 < len(tab) and tab[indiceVol+1] < heureMin:
            indiceVol = indiceVol + 1

        heureActuelle = heureMin

        while not place and retardAccumule <= 60 and heureActuelle <= heureMax:
            if indiceVol > indiceVolRetarde :
                ecart1 = ecartHeures(heureActuelle, tab[indiceVol])
                if ecart1 >= 5:
                    place = True
                    
            if indiceVol + 1 < len(tab) :
                ecart2 = ecartHeures(tab[indiceVol + 1], heureActuelle)
                if ecart2 >= 5:
                    place = True
                else:
                    place = False
            
            if place == 0 :
                if indiceVol + 1 < len(tab) :
                    if ecart2 == 0 :
                        indiceVol = indiceVol + 1
                        retardAccumule = retardAccumule + 5
                        heureActuelle = ajoutHeure(heureActuelle, 5)
                        
                    else:
                        retardAccumule = retardAccumule + ecart2
                        heureActuelle = ajoutHeure(heureActuelle, ecart2)
                
                else:
                    retardAccumule = retardAccumule + 1
                    heureActuelle = ajoutHeure(heureActuelle, 1)
    
        if place:
            tab[indiceVolRetarde] = heureActuelle
            decalerJusqua(tab, indiceVolRetarde, indiceVol)
        
        else:
            tab[indiceVolRetarde] = -1
            retardAccumule = -1
            decalerJusqua(tab, indiceVolRetarde, len(tab)-1)

    else:
        tab[indiceVolRetarde] = tab[indiceVolRetarde] + tpsRetard
        retardAccumule = tpsRetard
    
    return retardAccumule


# Fonction de test  
    
def tab_valide(tab):
    i = 1
    while i < len(tab):
        ecart = ecartHeures(tab[i],tab[i-1])
        if (ecart < 5 and ecart > -5) or (tab[i] < tab[i-1] and tab[i]!=-1) :
            return False
        i = i+1
    return True



cpt = 0
"""
taille = 10
tab=array([randint(0,20) for i in range(40)],'i')
tri_fusion(tab,0,39)
print(tab)
cpt = 0
print(recherche_dichotomie(tab, 12))
print(f"dichotomie : {cpt}")
cpt = 0
print(recherche_balayage(tab,12))
print(f"balayage : {cpt}")
cpt = 0
print(recherche_linéaire(tab,12))
print(f"linéaire : {cpt}")
cpt = 0
"""
tab=array([randint(0,20) for i in range(40)],'i')
tri_fusion(tab,0,39)
print(tab)
cpt = 0
print(rechercheBalayage2(tab, 12))
print(recherche_linéaire(tab,12))

            
