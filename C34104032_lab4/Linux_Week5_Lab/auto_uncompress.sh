#!/bin/bash

COMPRESSED_DIR="compressed_files"
ID_LIST="student_id"
MISSING_LIST="missing_list"
WRONG_LIST="wrong_list"
ZIP_DIR="compressed_files/zip"
TAR_GZ_DIR="compressed_files/tar.gz"
RAR_DIR="compressed_files/rar"
UNKNOWN_DIR="compressed_files/unknown"

# clean 
> "$MISSING_LIST"
> "$WRONG_LIST"

# create dirs
mkdir -p "$ZIP_DIR" "$TAR_GZ_DIR" "$RAR_DIR" "$UNKNOWN_DIR"

# scan every ID in student_id file and check missing in compressed_files/
while read -r student_id; do
    found=0
    for file in "$COMPRESSED_DIR"/*; do
        if [[ "$file" == *"$student_id"* ]]; then
            #found
            found=1
            break
        fi
    done
    # not found
    if [[ "$found" -eq 0 ]]; then
        echo "$student_id" >> "$MISSING_LIST"
    fi
done < "$ID_LIST"

# scan each file in compressed_files to find incorrect file formats
for file in "$COMPRESSED_DIR"/*; do
    # not checking the folders just created
    if [[ -f "$file" ]]; then
        filename=$(basename "$file")
        if [[ "$file" == *.zip ]]; then
            mv "$file" "$ZIP_DIR"
        elif [[ "$file" == *.tar.gz ]]; then
        mv "$file" "$TAR_GZ_DIR"
        elif [[ "$file" == *.rar ]]; then
        mv "$file" "$RAR_DIR"
        else
            # wrong format
            echo "$filename" >> "$WRONG_LIST"
            mv "$file" "$UNKNOWN_DIR"
        fi
    fi
done

# uncompress the other 3 groups of compressed files
for file in "$ZIP_DIR"/*.zip; do
    [[ -f "$file" ]] && unzip "$file" -d "$ZIP_DIR" && rm "$file"
done

for file in "$TAR_GZ_DIR"/*.tar.gz; do
    [[ -f "$file" ]] && tar -xzvf "$file" -C "$TAR_GZ_DIR" && rm "$file"
done

for file in "$RAR_DIR"/*.rar; do
    [[ -f "$file" ]] && unrar x "$file" "$RAR_DIR" && rm "$file"
done

