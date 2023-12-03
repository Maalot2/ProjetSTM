#include "findpeaks.h"


/**
 * @brief Calculer le seuil initial basé sur la moyenne ou la médiane des amplitudes du signal.
 *
 * @param Yin Tableau d'entrée représentant le signal.
 * @return Seuil initial.
 */
/*
float calculateInitialThreshold(float *Yin)
{
    // Vous pouvez choisir d'utiliser la moyenne ou la médiane ici
    // Exemple avec la moyenne :
    float sum = 0.0;
    for (int i = 0; i < LENGTHYIN; i++)
    {
        sum += Yin[i];
    }
    return sum / LENGTHYIN;
}
*/


/**
 * @brief Met à jour le seuil dynamique en fonction de la moyenne mobile des amplitudes des pics.
 *
 * @param recentAmplitude Amplitude du pic le plus récent.
 */
/*
float updateDynamicThreshold(float recentAmplitude, float dynamicThreshold)
{
    // Mettre à jour le seuil dynamique avec la moyenne mobile
    float d = ALPHA * recentAmplitude + (1 - ALPHA) * dynamicThreshold;
    return d;
}
*/



/**
 * @brief Trouve les pics dans un signal donné.
 *
 * @param Yin Tableau d'entrée représentant le signal.
 * @param Ypk Tableau de sortie pour stocker les amplitudes des pics.
 * @param numPeaks Pointeur vers la variable pour stocker le nombre de pics trouvés.
 */
void findpeaks(float *Yin, int *iPk)
{
    // Paramètres
    float MinPeakHeight = 5.0;
    float Threshold = 2.0;
    int i, j;

    // On rempli iPk de -1 car -1 correspond au valeurs d'erreur (pas de pic)
    for (int i = 0; i < LENGTHYIN; i++)
    {
        iPk[i] = -1;
    }

    // Trouver les pics
    getAllPeaks(Yin, iPk);

    // Supprimer les pics en dessous de MinPeakHeight
    removePeaksBelowMinPeakHeight(Yin, iPk, MinPeakHeight);

    // Supprimer les pics en dessus du thrashold
    removePeaksBelowThreshold(Yin, iPk, Threshold);
}



/**
 * @brief Trouve tous les pics dans un signal donné.
 *
 * @param Yin Tableau d'entrée représentant le signal.
 * @param iPk Tableau de sortie pour stocker les indices des pics.
 * @param iInflect Tableau de sortie pour stocker les indices des points d'inflexion.
 */
void getAllPeaks(float *Yin, int *iPk)
{
    // A voir si on veut faire d'autres traitements ici

    // On récupère les maximum locaux et les points d'inflexion
    findLocalMaxima(Yin, iPk);
}



/**
 * @brief Supprime les pics en dessous d'une certaine hauteur minimale.
 *
 * @param Yin Tableau d'entrée représentant le signal.
 * @param iPk Tableau des indices des pics à modifier.
 * @param MinPeakHeight Hauteur minimale requise pour conserver un pic.
 */
void removePeaksBelowMinPeakHeight(float *Yin, int *iPk, float MinPeakHeight) 
{
    for (int i = 0; i < LENGTHYIN; i++)
    {
        // Si on a un pic
        if(iPk[i] > 0)
        {
            // Si ce pic est inférieur à la valeur min souhaitée pour un pic
            if (Yin[iPk[i]] < MinPeakHeight)
            {
                iPk[i] = -1; // -1 pour dire que ce n'est pas un pic
            }
        }
    }
}


/**
 * @brief Supprime les indices des pics dont la valeur dans le signal est en dessous d'un certain seuil par rapport à leurs voisins immédiats
 *
 * @param Yin Tableau d'entrée représentant le signal.
 * @param iPk Tableau des indices des pics à modifier.
 * @param Threshold Seuil en dessous duquel un pic est supprimé.
 */
void removePeaksBelowThreshold(float *Yin, int *iPk, float Threshold)
{
    //float dynamicThreshold = calculateInitialThreshold(Yin);

    // Parcourir tous les indices dans iPk
    for (int i = 0; i < LENGTHYIN; i++)
    {
        // Si c'est un pic
        if(iPk[i] > 0)
        {
            // Calculer l'indice précédent et suivant dans Yin
            int prevIndex = iPk[i] - 2;
            int nextIndex = iPk[i] + 2;

            // Vérifier les limites du tableau d'entrée
            if(prevIndex >= 0 && nextIndex < LENGTHYIN)
            {
                // Calculer la valeur maximale entre les voisins immédiats
                float base = (Yin[prevIndex] > Yin[nextIndex]) ? Yin[prevIndex] : Yin[nextIndex];

                // Vérifier la condition de seuil
                if (Yin[iPk[i]] - base < Threshold)
                {
                    // Si la condition n'est pas satisfaite, -1 pour dire que ce n'est pas un pic
                    iPk[i] = -1;
                }
            }
            else
            {
                iPk[i] = -1;
            }
        }

        
        // Mettre à jour le seuil dynamique avec la moyenne mobile
        //dynamicThreshold = updateExpMovingAverage(Yin[i], dynamicThreshold);
        
    }
}


/**
 * @brief Trouve les pics locaux et les points d'inflection dans un signal.
 *
 * @param Yin Tableau d'entrée représentant le signal.
 * @param iPk Tableau de sortie pour stocker les indices des pics locaux.
 */
void findLocalMaxima(float *Yin, int *iPk)
{

    // Réalise la fonction sign et stock les coefficients 1 -1 et 0
    int s[LENGTHYIN - 1];
    for (int i = 0; i < LENGTHYIN - 1; i++)
    {
        s[i] = (Yin[i + 1] - Yin[i] > 0) ? 1 : ((Yin[i + 1] - Yin[i] < 0) ? -1 : 0);
    }

    // Trouver un maximum local ou un point d'inflection
    int maxCount = 0;
    for (int i = 0; i < LENGTHYIN - 2; i++)
    {
        if (s[i] > s[i + 1] || s[i] != s[i + 1]) // max local || point d'inflexion
        {
            iPk[maxCount] = i+1;
            maxCount++;
        }
    }
}


/* EXEMPLE TEST */
/*
int main()
{
    int iPk[LENGTHYIN];
    int i,j = 0;
float Yin[] = {4.269, 10.090, 20.319, 24.662, 35.034, 36.545, 29.552, 15.916, 12.246, 11.372, 20.081, 39.997, 17.889, 7.510, 6.123, 5.624, 15.980, 15.104, 5.839, 4.809, 4.014, 5.282, 8.493, 4.874, 3.432, 3.744, 3.459, 5.321, 4.940, 2.984, 2.795, 2.889, 6.140, 10.531, 6.656, 3.337, 3.221, 5.263, 10.351, 9.368, 3.718, 2.249, 2.181, 2.305, 2.400, 2.007, 1.793, 1.645, 1.886, 2.055, 2.008, 1.710, 1.474, 1.492, 1.523, 1.510, 1.319, 1.172, 1.172, 1.306, 1.425, 1.349, 1.217, 1.083, 1.091, 1.114, 1.159, 1.204, 1.140, 1.194, 1.286, 1.331, 1.201, 1.074, 1.066, 1.116, 1.190, 1.178, 1.199, 1.043, 1.081, 1.151, 1.046, 1.015, 0.961, 0.867, 0.786, 0.783, 0.763, 0.800, 0.709, 0.681, 0.736, 0.764, 0.835, 0.805, 0.705, 0.613, 0.644, 0.715, 0.747, 0.730, 0.706, 0.734, 0.771, 0.809, 0.821, 0.811, 0.858, 0.944, 1.011, 0.985, 0.969, 1.132, 1.177, 1.421, 1.531, 1.399, 1.243, 1.112, 1.080, 1.074, 1.048, 0.947, 0.887, 0.899, 0.744, 0.734, 0.776, 0.726, 0.665, 0.695, 0.669, 0.683, 0.676, 0.652, 0.668, 0.655, 0.571, 0.549, 0.538, 0.553, 0.650, 0.577, 0.591, 0.660, 0.689, 0.632, 0.626, 0.631, 0.657, 0.634, 0.711, 0.793, 0.859, 0.841, 0.792, 0.711, 0.656, 0.578, 0.610, 0.563, 0.556, 0.590, 0.562, 0.543, 0.494, 0.552, 0.553, 0.558, 0.532, 0.511, 0.522, 0.500, 0.479, 0.484, 0.459, 0.448, 0.436, 0.359, 0.349, 0.344, 0.357, 0.370, 0.370, 0.358, 0.358, 0.351, 0.343, 0.357, 0.349, 0.339, 0.362, 0.357, 0.357, 0.371, 0.351, 0.325, 0.327, 0.329, 0.322, 0.339, 0.310, 0.304, 0.281, 0.278, 0.284, 0.298, 0.286, 0.292, 0.308, 0.335, 0.321, 0.314, 0.305, 0.315, 0.335, 0.299, 0.308, 0.313, 0.292, 0.300, 0.294, 0.324, 0.304, 0.294, 0.295, 0.325, 0.330, 0.328, 0.316, 0.311, 0.326, 0.330, 0.333, 0.313, 0.310, 0.342, 0.324, 0.326, 0.337, 0.304, 0.254, 0.272, 0.276, 0.282, 0.246, 0.263, 0.272, 0.263, 0.252, 0.229, 0.236, 0.231, 0.236, 0.218, 0.204, 0.210, 0.185, 0.180, 0.178, 0.180, 0.176, 0.162, 0.154, 0.153, 0.148, 0.148, 0.152, 0.158, 0.134, 0.132, 0.129, 0.119, 0.124, 0.122, 0.107, 0.103, 0.100, 0.102, 0.098, 0.087, 0.085, 0.085, 0.081, 0.075, 0.065, 0.060, 0.060, 0.050, 0.047, 0.048, 0.041, 0.036, 0.033, 0.031, 0.028, 0.022, 0.021, 0.018, 0.015, 0.014, 0.012, 0.011, 0.009, 0.008, 0.007, 0.006, 0.004, 0.003, 0.002, 0.002, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.002, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.001, 0.002, 0.002, 0.003, 0.004, 0.006, 0.007, 0.008, 0.009, 0.011, 0.012, 0.014, 0.015, 0.018, 0.021, 0.022, 0.028, 0.031, 0.033, 0.036, 0.041, 0.048, 0.047, 0.050, 0.060, 0.060, 0.065, 0.075, 0.081, 0.085, 0.085, 0.087, 0.098, 0.102, 0.100, 0.103, 0.107, 0.122, 0.124, 0.119, 0.129, 0.132, 0.134, 0.158, 0.152, 0.148, 0.148, 0.153, 0.154, 0.162, 0.176, 0.180, 0.178, 0.180, 0.185, 0.210, 0.204, 0.218, 0.236, 0.231, 0.236, 0.229, 0.252, 0.263, 0.272, 0.263, 0.246, 0.282, 0.276, 0.272, 0.254, 0.304, 0.337, 0.326, 0.324, 0.342, 0.310, 0.313, 0.333, 0.330, 0.326, 0.311, 0.316, 0.328, 0.330, 0.325, 0.295, 0.294, 0.304, 0.324, 0.294, 0.300, 0.292, 0.313, 0.308, 0.299, 0.335, 0.315, 0.305, 0.314, 0.321, 0.335, 0.308, 0.292, 0.286, 0.298, 0.284, 0.278, 0.281, 0.304, 0.310, 0.339, 0.322, 0.329, 0.327, 0.325, 0.351, 0.371, 0.357, 0.357, 0.362, 0.339, 0.349, 0.357, 0.343, 0.351, 0.358, 0.358, 0.370, 0.370, 0.357, 0.344, 0.349, 0.359, 0.436, 0.448, 0.459, 0.484, 0.479, 0.500, 0.522, 0.511, 0.532, 0.558, 0.553, 0.552, 0.494, 0.543, 0.562, 0.590, 0.556, 0.563, 0.610, 0.578, 0.656, 0.711, 0.792, 0.841, 0.859, 0.793, 0.711, 0.634, 0.657, 0.631, 0.626, 0.632, 0.689, 0.660, 0.591, 0.577, 0.650, 0.553, 0.538, 0.549, 0.571, 0.655, 0.668, 0.652, 0.676, 0.683, 0.669, 0.695, 0.665, 0.726, 0.776, 0.734, 0.744, 0.899, 0.887, 0.947, 1.048, 1.074, 1.080, 1.112, 1.243, 1.399, 1.531, 1.421, 1.177, 1.132, 0.969, 0.985, 1.011, 0.944, 0.858, 0.811, 0.821, 0.809, 0.771, 0.734, 0.706, 0.730, 0.747, 0.715, 0.644, 0.613, 0.705, 0.805, 0.835, 0.764, 0.736, 0.681, 0.709, 0.800, 0.763, 0.783, 0.786, 0.867, 0.961, 1.015, 1.046, 1.151, 1.081, 1.043, 1.199, 1.178, 1.190, 1.116, 1.066, 1.074, 1.201, 1.331, 1.286, 1.194, 1.140, 1.204, 1.159, 1.114, 1.091, 1.083, 1.217, 1.349, 1.425, 1.306, 1.172, 1.172, 1.319, 1.510, 1.523, 1.492, 1.474, 1.710, 2.008, 2.055, 1.886, 1.645, 1.793, 2.007, 2.400, 2.305, 2.181, 2.249, 3.718, 9.368, 10.351, 5.263, 3.221, 3.337, 6.656, 10.531, 6.140, 2.889, 2.795, 2.984, 4.940, 5.321, 3.459, 3.744, 3.432, 4.874, 8.493, 5.282, 4.014, 4.809, 5.839, 15.104, 15.980, 5.624, 6.123, 7.510, 17.889, 39.997, 20.081, 11.372, 12.246, 15.916, 29.552, 36.545, 35.034, 24.662, 20.319, 10.090};    findpeaks(Yin, iPk);

    for(i=0; i < LENGTHYIN; i++)
    {
        if(iPk[i] > 0)
        {
            j++;
            printf("Amplitude %d : %f Indice : %d\n", j, Yin[iPk[i]], iPk[i]);
        }

    }

    system("pause");

    return 0;
}
*/
