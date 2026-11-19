#include <iostream>
#include <string>

struct Session
{
    bool Wait()
    {
        if (ouverte)
        {
            ++refus;
            return false;
        }
        return true;
    }

    bool Begin()
    {
        if (ouverte)
        {
            ++refus;
            return false;
        }
        ouverte = true;
        ++debuts;
        return true;
    }

    bool End()
    {
        if (!ouverte)
        {
            ++refus;
            return false;
        }
        ouverte = false;
        ++fins;
        return true;
    }

    bool ouverte = false;
    int debuts = 0;
    int fins = 0;
    int refus = 0;
};

class GardeTrame
{
public:
    explicit GardeTrame(Session& session) : session_(session)
    {
    }

    ~GardeTrame()
    {
        session_.End();
    }

    GardeTrame(const GardeTrame&) = delete;
    GardeTrame& operator=(const GardeTrame&) = delete;

private:
    Session& session_;
};

char signeEffectif(char c, bool etat)
{
    if (!etat && (c == 'N' || c == 'C'))
    {
        return 'V';
    }
    return c;
}

int boucleSansGarde(Session& s, const std::string& mot)
{
    int images = 0;
    for (char c : mot)
    {
        bool etat = s.Wait();
        s.Begin();
        char signe = signeEffectif(c, etat);

        if (signe == 'N')
        {
            ++images;
        }
        if (signe == 'C')
        {
            continue;
        }
        if (signe == 'R')
        {
            return images;
        }
        s.End();
    }
    return images;
}

int boucleAvecGarde(Session& s, const std::string& mot)
{
    int images = 0;
    for (char c : mot)
    {
        bool etat = s.Wait();
        s.Begin();
        GardeTrame garde(s);
        char signe = signeEffectif(c, etat);

        if (signe == 'N')
        {
            ++images;
        }
        if (signe == 'C')
        {
            continue;
        }
        if (signe == 'R')
        {
            return images;
        }
    }
    return images;
}

void afficher(const std::string& nom, const Session& s, int images)
{
    std::cout << nom << " DEBUTS " << s.debuts << " FINS " << s.fins
              << " REFUS " << s.refus << " IMAGES " << images
              << " OUVERTE " << (s.ouverte ? "OUI" : "NON") << "\n";
}

int main()
{
    int T = 0;
    std::cin >> T;

    std::string mot;
    if (T > 0)
    {
        std::cin >> mot;
    }

    Session sans;
    int imagesSans = boucleSansGarde(sans, mot);
    afficher("SANS", sans, imagesSans);

    Session avec;
    int imagesAvec = boucleAvecGarde(avec, mot);
    afficher("AVEC", avec, imagesAvec);
    return 0;
}
