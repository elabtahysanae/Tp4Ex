#include <iostream>
#include <string>
using namespace std;

class Marque
{
private:
    string code;
    string nom;

public:

    Marque()
    {
        this->code = "";
        this->nom = "";
    }


    Marque(string code, string nom)
    {
        this->code = code;
        this->nom = nom;
    }

    void affiche()
    {
        cout << "Code: " << code << endl;
        cout << "Nom de la marque: " << nom << endl;
    }

    void setCode(string code)
    {
        this->code = code;
    }


    void setNom(string nom)
    {
        this->nom = nom;
    }


    string getCode()
    {
        return code;
    }

    string getNom()
    {
        return nom;
    }
    void saisie()
    {

        cout << "Saisir le code de la marque : ";
        cin >> code;
        cout << "Saisir le nom de la marque : ";
        cin >> nom;
    }


};

class Article
{
private:
    static int compteur;
    int referenceArticle;
    float prixHT;
    Marque marque;
    float tva;


public:

    Article(string c, string m, float prixHT, Marque marque, float tva)
    {
        this->referenceArticle = ++compteur;
        this->prixHT = prixHT;
        marque.setCode(c);
        marque.setNom(m);
        this->marque = marque;
        this->tva = tva;
    }
    Article()
    {
        referenceArticle = ++compteur;
        prixHT = 0.0;
        tva = 0.0;
        marque = Marque();
    }


    ~Article()
    {
        cout << "Destruction de l'objet" << endl;
    }


    Article(const Article& ar)
    {
        this->referenceArticle = ++compteur;
        this->prixHT = ar.prixHT;
        this->marque = ar.marque;
        this->tva = ar.tva;
    }

    int getReferenceArticle()
    {
        return referenceArticle;
    }


    void setPrixHT(float prixHT)
    {
        this->prixHT = prixHT;
    }


    float getPrixHT()
    {
        return prixHT;
    }


    Marque getMarque()
    {
        return marque;
    }


    void setMarque(Marque marque)
    {
        this->marque = marque;
    }


    float getTva()
    {
        return tva;
    }


    void setTva(float tva)
    {
        this->tva = tva;
    }

    void saisie()
    {

        float prixHT, tva;

        cout << "Saisir le prix HT : ";
        cin >> prixHT;
        cout << "Saisir la TVA : ";
        cin >> tva;
        marque.saisie();
    }
    void affichage ()
    {
        cout << "Référence Article: " << referenceArticle << endl;
        cout << "Prix HT: " << prixHT << endl;
        marque.affiche();
        cout << "TVA: " << tva << "%" << endl;

    }
    bool comparer (Article ar)
    {
        if(calculPrixTTC()>ar.calculPrixTTC())
        {
            return true ;
        }
        return false;
    }
    float calculPrixTTC ()
    {
        return prixHT+prixHT*tva;

    }
    Article maxPrix(Article a)
    {
        if (calculPrixTTC() > a.calculPrixTTC())
        {
            return *this;
        }
        else
        {
            return a;
        }

    }


};
class HyperMarche
{
    string nom;
    string adresse;
    int rue;
    Article *tab;
    int taille;
    int posLibre;

public :
    HyperMarche(string n,string a, int r,int t)
    {
        nom=n;
        adresse=a;
        rue=r;
        taille=t;
        tab=new Article[taille];
        posLibre=0;

    }
    ~HyperMarche()
    {
        delete [] tab;

    }
    // Constructeur de recopie
    HyperMarche(HyperMarche& autre)
    {
        nom = autre.nom;
        adresse = autre.adresse;
        rue = autre.rue;
        taille = autre.taille;
        posLibre = autre.posLibre;


        tab = new Article[taille];


        for (int i = 0; i < posLibre; ++i)
        {
            tab[i] = autre.tab[i];
        }
    }
    string getNom() const
    {
        return nom;
    }
    string getAdresse() const
    {
        return adresse;
    }
    int getRue() const
    {
        return rue;
    }
    int getTaille() const
    {
        return taille;
    }
    int getPosLibre() const
    {
        return posLibre;
    }
    Article* getTab() const
    {
        return tab;
    }

    void setNom(const string& n)
    {
        nom = n;
    }
    void setAdresse(const string& a)
    {
        adresse = a;
    }
    void setRue(int r)
    {
        rue = r;
    }

    void setTaille(int t)
    {
        taille = t;
    }
    void setPosLibre(int p)
    {
        posLibre = p;
    }

    void affichage()
    {
        cout << "\n--- Informations de l'Hypermarché ---\n";
        cout << "Nom : " << nom << endl;
        cout << "Adresse : " << adresse << endl;
        cout << "Rue : " << rue << endl;
        cout << "Taille maximale du stock : " << taille << endl;
        cout << "Nombre d'articles enregistrés : " << posLibre << endl;

        if (posLibre == 0)
        {
            cout << "Aucun article dans le stock.\n";
        }
        else
        {
            cout << "\n--- Articles en stock ---\n";
            for (int i = 0; i < posLibre; ++i)
            {
                cout << "\nArticle " << (i + 1) << " :\n";
                tab[i].affichage();
            }
        }
    }
    Article maxPrix()
    {
        if (posLibre == 0)
        {
            cout << "Aucun article dans le stock." << endl;

        }

        Article ar = tab[0];
        for (int i = 1; i < posLibre; ++i)
        {

            ar=  ar.maxPrix(tab[i]);

        }
        return ar;
    }
    float MoyPrix()
    {

        if (posLibre == 0)
        {
            cout << "Aucun article dans le stock." << endl;

        }


        float sommePrix = 0.0f;


        for (int i = 0; i < posLibre; ++i)
        {
            sommePrix += tab[i].calculPrixTTC();
        }


        return sommePrix / posLibre;
    }
    bool findArticleByRef(int refer)
{
    for (int i = 0; i < posLibre; ++i)
    {
        if (tab[i].getReferenceArticle() == refer)
        {
            return true;
        }
    }
    return false;
}

int nbrArticleAvecMemeMarque(string marque ){
int count=0;
for(int i=0;i<posLibre,i++){
    if(tab[i].getMarque().getNom()==marque){

        count++;
    }

    return count;
}



}





    };



    int Article::compteur = 0;

    int main()
    {


        Marque m1("001", "Nike");
        m1.affiche();

        m1.setCode("002");
        m1.setNom("Adidas");
        cout << "Après modification :\n";
        m1.affiche();

        cout << "Code obtenu : " << m1.getCode() << endl;
        cout << "Nom obtenu : " << m1.getNom() << endl;

        cout << "\nSaisie d'une nouvelle marque :\n";
        Marque m2("", "");
        m2.saisie();
        m2.affiche();


        Article a1("123", "Nike", 100.0f, m1, 0.2f);
        Article a2("456", "Adidas", 150.0f, m2, 0.2f);

        cout << "\nArticle 1 :\n";
        a1.affichage();
        cout << "\nArticle 2 :\n";
        a2.affichage();

        cout << "\nAncien prix de a1: " << a1.getPrixHT() << endl;
        a1.setPrixHT(120.0f);
        cout << "Nouveau prix de a1: " << a1.getPrixHT() << endl;


        cout << "Prix TTC de a1: " << a1.calculPrixTTC() << endl;
        cout << "Prix TTC de a2: " << a2.calculPrixTTC() << endl;


        if (a1.comparer(a2))
        {
            cout << "a1 est plus cher que a2\n";
        }
        else
        {
            cout << "a2 est plus cher que ou égal à a1\n";
        }
// Création d'un hypermarché
        cout << "\n--- Création d'un hypermarché ---\n";
        HyperMarche h("Marjane", "Bd Zerktouni", 12, 5); // taille max 5

        // Ajout manuel d’articles dans le stock
        cout << "\n--- Ajout d'articles dans l'hypermarché ---\n";

        if (h.getPosLibre() < h.getTaille())
        {
            h.getTab()[h.getPosLibre()] = a1;
            h.setPosLibre(h.getPosLibre() + 1);
        }

        if (h.getPosLibre() < h.getTaille())
        {
            h.getTab()[h.getPosLibre()] = a2;
            h.setPosLibre(h.getPosLibre() + 1);
        }

        // Saisie et ajout d’un nouvel article
        cout << "\n--- Saisie d’un nouvel article à ajouter ---\n";
        Article a3;
        a3.saisie();

        if (h.getPosLibre() < h.getTaille())
        {
            h.getTab()[h.getPosLibre()] = a3;
            h.setPosLibre(h.getPosLibre() + 1);
        }
        else
        {
            cout << "Stock plein, impossible d'ajouter l'article.\n";
        }

        // Affichage final
        cout << "\n--- Affichage de l'hypermarché et des articles ---\n";
        h.affichage();

        cout << "\n--- Test de la méthode maxPrix ---\n";
        if (h.getPosLibre() > 0)
        {
            Article articlePlusCher = h.maxPrix();  // Appel de maxPrix() pour obtenir l'article le plus cher
            cout << "L'article avec le plus grand prix TTC est :\n";
            articlePlusCher.affichage();  // Affiche l'article avec le prix TTC le plus élevé
        }
        else
        {
            cout << "Le stock est vide, aucun article à comparer.\n";  // Message si le stock est vide
        }

        cout << "La moyenne des prix des articles est : " << h.MoyPrix() << endl;

        int refCherchee;
        cout << "Entrez la référence de l'article à chercher : ";
        cin >> refCherchee;

        if (h.findArticleByRef(refCherchee))
        {
            cout << "Article trouvé dans le stock." << endl;
        }
        else
        {
            cout << "Article non trouvé." << endl;
        }




        return 0;
    }
