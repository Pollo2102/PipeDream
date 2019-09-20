#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "elf.h"

int  dumpBufferToHex(uint8_t *buffer, int count, FILE *f);
void paddFile(int curr_size, int new_size, FILE *f);
void ehdrToLE(Elf32_Ehdr *ehdr);
void shdrToLE(Elf32_Shdr *shdr);
void phdrToLE(Elf32_Phdr *phdr);
Elf32_Shdr* loadSectionHeaders(Elf32_Ehdr *elf_hdr, FILE *f);
char*       loadSectionContent(Elf32_Shdr *shdr, FILE *f);

int main(int argc, char *argv[])
{
    if (argc != 6) {
        printf("Usage: %s <elf executable file> <code output file> <data output file> <code size> <data size>\n", argv[0]);
        printf("Where: <code size> is the number of words (32 bits) to include in the code file.\n");
        printf("       <data size> is the number of words (32 bits) to include in the data file.\n");
        return 1;
    }
    
    FILE *f, *fcode, *fdata;
    Elf32_Ehdr ehdr;
    
    f = fopen(argv[1], "rb");
    
    if (f == NULL) {
        printf("Cannot open file %s\n", argv[1]);
        return 1;
    }
    
    fcode = fopen(argv[2], "wb+");
    
    if (fcode == NULL) {
        printf("Cannot open output file %s\n", argv[2]);
        fclose(f);
        return 1;
    }
    
    fdata = fopen(argv[3], "wb+");
    
    if (fcode == NULL) {
        printf("Cannot open output file %s\n", argv[3]);
        fclose(f);
        fclose(fcode);
        return 1;
    }
    
    int code_size, data_size;

    code_size = atoi(argv[4]);
    data_size = atoi(argv[5]);
    
    fread( (char*)&ehdr, 1, sizeof(Elf32_Ehdr), f );   
   
    if (ehdr.e_ident[4] != ELFCLASS32) {
        printf("The file is not a MIPS32 executable file\n");
        fclose(f);
        fclose(fcode);
        fclose(fdata);
        return 1;
    }
    
    if (ehdr.e_ident[5] == ELFDATA2MSB) {
        ehdrToLE(&ehdr);
    }
    
    /* Program Headers */
    Elf32_Phdr phdr;
    
    fseek(f, ehdr.e_phoff, SEEK_SET);
    
    /* Section headers */
    Elf32_Shdr *sectionHeaders = loadSectionHeaders(&ehdr, f);
    char *stringTable = loadSectionContent(&sectionHeaders[ehdr.e_shstrndx], f);
    int i;
    
    // Dump text section
    printf("Dumping text section...\n");
    for (i = 0; i < ehdr.e_shnum; i++) {
        char *section_name = &stringTable[sectionHeaders[i].sh_name];
        
        if (strncmp(section_name, ".text", 4) == 0) {
           char *sectionContent = loadSectionContent(&sectionHeaders[i], f);
           int word_count;
           
           word_count = dumpBufferToHex(sectionContent, sectionHeaders[i].sh_size, fcode);
           paddFile(word_count, code_size, fcode);
           free(sectionContent);
        }
    }
    
    // Dump data section
    printf("Dumping data section ...\n");
    int word_count;
    
    for (i = 0; i < ehdr.e_shnum; i++) {
        char *section_name = &stringTable[sectionHeaders[i].sh_name];
        
        if (strcmp(section_name, ".data") == 0 ||
            strcmp(section_name, ".got") == 0) {
           int size_word_aligned = ((sectionHeaders[i].sh_size + 3) / 4) * 4;
           char *sectionContent = loadSectionContent(&sectionHeaders[i], f);
           word_count = dumpBufferToHex(sectionContent, size_word_aligned, fdata);
           free(sectionContent);
        } else if (strcmp(section_name, ".bss") == 0) {
            int size_word_aligned = ((sectionHeaders[i].sh_size + 3) / 4) * 4;
            char *sectionContent = malloc(size_word_aligned);
            memset(sectionContent, 0, sectionHeaders[i].sh_size);
            word_count += dumpBufferToHex(sectionContent, size_word_aligned, fdata);
            free(sectionContent);
        }
    }
    paddFile(word_count, data_size, fdata);
   
    free(stringTable);
    free(sectionHeaders);

    fclose(f);
    fclose(fcode);
    fclose(fdata);
}

int dumpBufferToHex(uint8_t *buffer, int count, FILE *f) {
    int word_count = 0;
    
    for (int i = 0; i < count; i++) {
        fprintf(f, "%02X", buffer[i]);
        if (i % 4 == 3) {
            fprintf(f, "\n");
            word_count++;
        }
    }
    
    return word_count;
}

void paddFile(int curr_size, int new_size, FILE *f) {
    int word_count = new_size - curr_size;
    
    for (int i = 0; i < word_count; i++) {
        fprintf(f, "00000000\n");
    }
}

Elf32_Half hwordToLE(Elf32_Half hword) {
    Elf32_Half result;
    
    result = ((hword & 0xff00) >> 8);
    result |= ((hword & 0x00ff) << 8);
    
    return result;
}

Elf32_Word wordToLE(Elf32_Word word) {
    Elf32_Word result;
    
    result = ((word & 0xff000000) >> 24);
    result |= ((word & 0x00ff0000) >> 8);
    result |= ((word & 0x0000ff00) << 8);
    result |= ((word & 0x000000ff) << 24);
    
    return result;
}

void ehdrToLE(Elf32_Ehdr *ehdr) {
    ehdr->e_type = hwordToLE(ehdr->e_type);
    ehdr->e_machine = hwordToLE(ehdr->e_machine);
    ehdr->e_version = wordToLE(ehdr->e_version);
    ehdr->e_entry = wordToLE(ehdr->e_entry);
    ehdr->e_phoff = wordToLE(ehdr->e_phoff);
    ehdr->e_shoff = wordToLE(ehdr->e_shoff);
    ehdr->e_flags = wordToLE(ehdr->e_flags);
    ehdr->e_ehsize = hwordToLE(ehdr->e_ehsize);
    ehdr->e_phentsize = hwordToLE(ehdr->e_phentsize);
    ehdr->e_ehsize = hwordToLE(ehdr->e_ehsize);
    ehdr->e_phnum = hwordToLE(ehdr->e_phnum);
    ehdr->e_shentsize = hwordToLE(ehdr->e_shentsize);
    ehdr->e_shnum = hwordToLE(ehdr->e_shnum);
    ehdr->e_shstrndx = hwordToLE(ehdr->e_shstrndx);   
}

void phdrToLE(Elf32_Phdr *phdr) {
    phdr->p_type = wordToLE(phdr->p_type);
    phdr->p_offset = wordToLE(phdr->p_offset);
    phdr->p_vaddr = wordToLE(phdr->p_vaddr);
    phdr->p_paddr = wordToLE(phdr->p_paddr);
    phdr->p_filesz = wordToLE(phdr->p_filesz);
    phdr->p_memsz = wordToLE(phdr->p_memsz);
    phdr->p_flags = wordToLE(phdr->p_flags);
    phdr->p_align = wordToLE(phdr->p_align);
}

void shdrToLE(Elf32_Shdr *shdr) {
    shdr->sh_name = wordToLE(shdr->sh_name);
    shdr->sh_type = wordToLE(shdr->sh_type);
    shdr->sh_flags = wordToLE(shdr->sh_flags);
    shdr->sh_addr = wordToLE(shdr->sh_addr);
    shdr->sh_offset = wordToLE(shdr->sh_offset);
    shdr->sh_size = wordToLE(shdr->sh_size);
    shdr->sh_link = wordToLE(shdr->sh_link);
    shdr->sh_info = wordToLE(shdr->sh_info);
    shdr->sh_addralign = wordToLE(shdr->sh_addralign);
    shdr->sh_entsize = wordToLE(shdr->sh_entsize);    
}

Elf32_Shdr *loadSectionHeaders(Elf32_Ehdr *elf_hdr, FILE *f) {
    Elf32_Shdr *sectionHeaders = malloc(elf_hdr->e_shnum * sizeof(Elf32_Shdr));
    
    fseek(f, elf_hdr->e_shoff, SEEK_SET);
    
    for (int i = 0; i < elf_hdr->e_shnum; i++) {
        
        fread((char *)&(sectionHeaders[i]), 1, sizeof(Elf32_Shdr), f);
      
        if (elf_hdr->e_ident[5] == ELFDATA2MSB) {
            shdrToLE(&(sectionHeaders[i]));
        }
    }   
    
    return sectionHeaders;
}

char *loadSectionContent(Elf32_Shdr *shdr, FILE *f) {
    int size_word_aligned = ((shdr->sh_size + 3) / 4) * 4;
    char *buff = malloc(size_word_aligned);
    
    if (buff == NULL)
        return NULL;
    
    long origPos = ftell(f);
    
    memset(buff, 0, size_word_aligned);
    fseek(f, shdr->sh_offset, SEEK_SET);
    fread(buff, 1, shdr->sh_size, f);
    fseek(f, origPos, SEEK_SET);
    
    return buff;
}