# Importation des modules

from random import *
from numpy import *
import time


# Définition des fonctions

def fusion(t,d,f):
    global cpt
    r=zeros(f-d+1,'i') # 1
    m=(d+f)//2 # 3
    i1=d # 1
    i2=m+1 # 2
    k=0 # 1
    cpt = cpt+8
    while (i1<=m and i2 <=f): # 3
        if (t[i1] < t[i2]): # 3
            r[k] = t[i1] # 3
            i1=i1+1 # 2
            cpt = cpt+5
        else:
            r[k] = t[i2] # 3
            i2=i2+1 # 2
            cpt = cpt+5
        k=k+1 # 2
        cpt = cpt+6
    cpt = cpt+3
    while (i1 <=m): # 1
        cpt = cpt+8
        r[k] = t[i1] # 3
        i1=i1+1 # 2
        k=k+1 # 2
    cpt = cpt+1
    while (i2 <=f): # 1
        r[k] = t[i2] # 3
        i2=i2+1 # 2
        k=k+1 # 2
        cpt = cpt+8
    k=0
    cpt = cpt+2
    while k <= (f-d): # 2
        t[d+k]=r[k] # 4
        k=k+1 # 2
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
    
def tri_ultime(tab):
    global cpt
    cpt = cpt+5
    if len(tab)<2 or len(tab)>25: # 5
        tri_fusion(tab,0,len(tab)-1)
    else:
        tri_selection(tab)
    
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



def recherche_dichotomie(tab,val):
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
    j = len(tab) - 1
    i_val = -1
    cpt = cpt + m # 5 opérations élémentaires avant la boucle
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



def create_tab_heure(taille,step_max):
    tab=zeros(taille,'i')
    tab[0] = randint(360,700)
    i = 1
    while i<len(tab):
        tab[i] = tab[i-1]+randint(5,step_max)
        i=i+1
    return tab



def ecart_heures(heure1,heure2):
    global cpt
    cpt = cpt +3
    if heure2 > heure1:
        ecart = heure2-heure1
    else:
        ecart = heure1-heure2
    return ecart
        


def decaler_vol(tab,deb,fin):
    global cpt
    tmp = tab[deb]
    cpt = cpt + 2
    while deb<fin:
        tab[deb]=tab[deb+1]
        deb = deb + 1
        cpt = cpt + 7
    tab[fin]=tmp
    cpt = cpt + 2
    
    
    
def afficher_tab_heure(tab):
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


def ajout_retard(tab,indice_vol_retarde,tps_retard):
    heure_min = tab[indice_vol_retarde] + tps_retard
    indice_vol = indice_vol_retarde
    
    if heure_min <=1320:
            
        if len(tab) > 1:
            place = False
            retard_accumule = 0
            
            while indice_vol + 1 < len(tab) and tab[indice_vol+1] < heure_min:
                retard_accumule = retard_accumule + ecart_heures(tab[indice_vol],tab[indice_vol+1])
                indice_vol = indice_vol + 1
            
            if indice_vol + 1 < len(tab) and tab[indice_vol+1] - 5 >= heure_min and retard_accumule - 5 <= 60:
                tab[indice_vol_retarde] = tab[indice_vol+1] - 5
                place = True
        
            while not place and indice_vol + 1 < len(tab) and retard_accumule <= 60:
                ecart = ecart_heures(tab[indice_vol],tab[indice_vol+1])
                
                if tab[indice_vol] +5 >= heure_min:
                    
                    if ecart >= 10 and tab[indice_vol] + 5 <= 1320:
                        tab[indice_vol_retarde] = tab[indice_vol] + 5
                        retard_accumule = retard_accumule + 5
                        place = True
                    
                if not place:
                    indice_vol = indice_vol + 1
                    retard_accumule = retard_accumule + ecart
        
            if not place and retard_accumule <= 60 and tab[len(tab)-1] + 5 <= 1320:
                if tab[len(tab)-1] + 5 >= heure_min:
                    tab[indice_vol_retarde] = tab[len(tab)-1] + 5
                    retard_accumule = retard_accumule + 5
                else:
                    tab[indice_vol_retarde] = heure_min
                    retard_accumule = tps_retard
 
            if retard_accumule > 60 or retard_accumule == -1:
                tab[indice_vol_retarde] = -1
                retard_accumule = -1
                decaler_vol(tab,indice_vol_retarde,len(tab)-1)
        
            else:
                decaler_vol(tab,indice_vol_retarde,indice_vol)
        
        else:
            tab[0] = heure_min
            retard_accumule = tps_retard
    
    else:
        tab[indice_vol_retarde] = -1
        retard_accumule = -1
        if len(tab) > 1:
            decaler_vol(tab,indice_vol_retarde,len(tab)-1)
                
            
    return retard_accumule
                
def test_optimisation(tab,indice_vol_retarde,tps_retard):
    heure_min = tab[indice_vol_retarde] + tps_retard
    heure_max = tab[indice_vol_retarde] + 60
    print(heure_min)
    print(heure_max)
    i = indice_vol_retarde
    i_max = -1
    tmp = zeros(len(tab)+2,'i')
    tmp[1] = heure_min
    k = 2
    while i < len(tab) and i_max == -1 and i < len(tab):
        if tab[i] >=heure_min:
            if tmp[0] == 0:
                tmp[0] = tab[i-1]
            if tab[i] >= heure_max:
                i_max = i-1
            else:
                tmp[k] = tab[i]
                k = k + 1
        i = i + 1      
    tmp[k] = heure_max
    tmp[k+1] = tab[i+1]
    k_max = k
    k = 3
    place = False
    ecart = ecart_heures(tmp[0],tmp[2])
    if ecart >= 10 and tmp[2]:
        print('a')
    while k < k_max - 2 and not place:
        ecart = ecart_heures(tmp[k],tmp[k+1])
        if tmp[k] + 5 <= tmp[k_max] and ecart >=10:
            print('fuck')
    
    
    return tmp
    
def tab_valide(tab):
    i = 1
    while i < len(tab):
        if ecart_heures(tab[i],tab[i-1]) < 5 or (tab[i] < tab[i-1] and tab[i]!=-1) :
            return False
        i = i+1
    return True



cpt = 0

taille = 10
tab=create_tab_heure(taille,20)
a = randint(0,taille-1)
b = randint(0,60)
print(f"heure_min : {tab[a] + b}")
tab2 = copier(tab)
print(f"retard : {ajout_retard(tab,a,b)}")
print(f"a = {a} b = {b}")
for i in range(len(tab)):
    print(f"{i}:{tab2[i]}",end=' ')
print(' ')
for i in range(len(tab)):
    print(f"{i}:{tab[i]}",end=' ')
print(' ')
print(test_optimisation(tab,0,20))
    
            