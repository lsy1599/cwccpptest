// Text file I/O - Unicode/ASCII/ANSI/UTF-8

// ----------------------------------------------------------------------------
// class TextFile

// filemode
#define TF_READ         1                  // existing file
#define TF_WRITE        2                  // new file
#define TF_APPEND       3                  // append to existing file

// encoding
#define TF_ANSI         1
#define TF_UTF16LE      2
#define TF_UTF16BE      3
#define TF_UTF8         4

#define TF_UNIX         0x100               // write out line-ends as \n, not \r\n

// Error codes for ReadByte / ReadChar functions (negative)
#define TF_EOF          -1
#define TF_ERROR        -2


class TextFileReader;
class TextFileWriter;
class ANSI_TextFileReader;


class TextFile
{
public:

// Constructor
TextFile::TextFile ();

// Destructor
TextFile::~TextFile ();

// Open (not in constructor, lest it fail); sets last error code and string
int TextFile::Open (TCHAR *filename, int filemode, int encoding = 0, int bufsize = 0);

// Close; sets last error code and string if can't flush buffer
int TextFile::Close (void);

// Flush our buffer; sets last error code and string on error
int TextFile::Flush (void);

// ReadLine; line_buf is allocated with alloc_block and may initially be NULL
int TextFile::ReadLine (BOOL *data_lost, TCHAR **line_buf);

// Read a character.  Note that, for unicode files, this reads a unicode character
int TextFile::ReadChar (void);

// Write a string; sets last error code and string on error
int TextFile::WriteString (BOOL *data_lost, TCHAR *s);

// printf, effectively; sets last error code and string on error
int TextFile::FormatString (BOOL *data_lost, TCHAR *s, ...);

// printf, effectively; sets last error code and string on error
int TextFile::vFormatString (BOOL *data_lost, TCHAR *s, va_list ap);

// Write a character; sets last error code and string on error
int TextFile::WriteChar (BOOL *data_lost, int ch);

// Return the file encoding (for TF_READ)
int TextFile::GetEncoding (void) { return this->encoding; }

// Set code page; can do this without opening the file
void TextFile::SetCodePage (int code_page) { this->code_page = code_page; }

// Set 'unknown' character; can do this without opening the file
void TextFile::SetUnknownChar (char *unknown_char);

// Return ANSI characters read from file unchanged
// For ANSI-files only.
// Note that ReadLine then returns chars, not TCHAR's
void TextFile::SetAnsiPassThru (bool passthru);

// Return ANSI characters read from file unchanged (but widened)
// For ANSI-files only.
inline bool TextFile::GetAnsiPassThru (void) { return this->ansi_passthru; }

private:

// Create textfile reader and read BOM
int TextFile::CreateFileReader (void);

// Create textfile writer
void TextFile::CreateFileWriter (void);

private:
    TCHAR   *filename;
    int     filemode;
    int     encoding;
    int     encoding_flags;
    bool    ansi_passthru;
    int     bufsize;
    HANDLE  hFile;
    TextFileReader *file_reader;
    TextFileWriter *file_writer;
    bool    need_bom;
    int     code_page;
    char    *unknown_char;
};
