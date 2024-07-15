def read_data_from_file(file_path):
    """Reads data from a file and returns a list of floats without any occurrences of 2.0.

    Parameters:
    - file_path: Path to the file.

    Returns:
    - List of floats without any occurrences of 2.0.
    """
    with open(file_path, "r") as file:
        lines = file.readlines()
        data = [float(line.strip()) for line in lines if float(line.strip()) != 2.0]
    return data
