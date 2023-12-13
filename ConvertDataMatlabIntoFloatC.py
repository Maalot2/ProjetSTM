import re

def convert_to_normal_number(matlab_number):
    return '{:.15f}'.format(float(matlab_number))

def process_file(input_file, output_file):
    with open(input_file, 'r') as file:
        lines = file.readlines()

    processed_numbers = []
    for line in lines:
        # Utilise une expression régulière pour trouver et remplacer la notation exponentielle de style MATLAB
        modified_line = re.sub(r'([0-9.]+)e(-?[0-9]+)', lambda x: convert_to_normal_number(x.group(0)), line)
        processed_numbers.append(modified_line)

    # Écrire les nombres modifiés dans un fichier temporaire
    temp_output_file = 'temp_output.txt'
    with open(temp_output_file, 'w') as file:
        file.writelines(processed_numbers)

    # Lire le contenu du fichier temporaire
    with open(temp_output_file, "r") as f:
        lines = f.readlines()

    # Modifier les nombres et construire la nouvelle chaîne
    modified_numbers = []
    for line in lines:
        number = float(line.strip())  # Convertir la chaîne en nombre
        modified_numbers.append(f"{number:.3f}")  # Formater le nombre avec trois chiffres après la virgule

    # Construire la chaîne résultante avec crochets et virgules
    result_string = "float Yin[] = {" + ", ".join(modified_numbers) + "};"

    # Écrire la chaîne résultante dans un nouveau fichier
    with open(output_file, 'w') as file:
        file.write(result_string)

    # Supprimer le fichier temporaire
    import os
    os.remove(temp_output_file)

# Exemple d'utilisation
input_filename = 'input.txt'
output_filename = 'output.h'
process_file(input_filename, output_filename)
