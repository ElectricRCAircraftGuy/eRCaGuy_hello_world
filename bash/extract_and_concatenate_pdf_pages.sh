#!/bin/bash

# GS
# ~Mar. 2024

# Take pg 3 of most pdfs, and pg 4 of some pdfs, and combine them all into a single PDF. 
#
# NB: the files should be named such that they naturally sort alphabetically in the glob as shown
# by `ls -1 *.pdf`! Example filenames that work well for this script are: 
#
# "20240401_bank_amended_signature_card(01).pdf"
# "20240401_bank_amended_signature_card(02).pdf"
# "20240401_bank_amended_signature_card(03).pdf"
# "20240401_bank_amended_signature_card(04).pdf"
#
# Do NOT start with (00) in the number! I think that doesn't work well with the glob? Not 100% sure.

# Usage:
# ```
# cd /path/to/pdf/files
# /path/to/extract_and_concatenate_pdf_pages.sh
# ```


# Loop over all PDFs
count=0
for pdf in *.pdf; do
    ((count++))

    # debugging: print the name of the PDF being processed, to ensure that they are being processed
    # in the correct, expected order!
    echo "pdf = $pdf"

    # extract pg 3 for most PDFs
    pg="3"

    # But extract pg 4 for these PDFs
    case "$count" in 5|6|13|15|19|20|24|25)
        pg="4"
    esac

    count_str=$(printf "%02d" $count)
    echo "count_str = $count_str"  # debugging

    pdftk "$pdf" cat "$pg" output "extracted_$count_str".pdf
done

sleep 2

# Combine all extracted pages into one PDF now
pdfunite extracted_*.pdf extracted_combined.pdf
