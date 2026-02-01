using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace FileExplorer
{
    class Program
    {
        private static string currentDirectory;
        private static Stack<string> directoryHistory;

        static void Main(string[] args)
        {
            currentDirectory = Directory.GetCurrentDirectory();
            directoryHistory = new Stack<string>();

            Console.WriteLine("File Explorer - Type 'help' voor beschikbare commando's.");
            Console.WriteLine($"huidige directory: {currentDirectory}\n");

            while (true)
            {
                Console.Write($"{currentDirectory}> ");
                string input = Console.ReadLine()?.Trim();

                if (string.IsNullOrEmpty(input))
                    continue;

                string[] parts = input.Split(' ', 2);
                string command = parts[0].ToLower();
                string argument = parts.Length > 1 ? parts[1] : "";

                try
                {
                    switch (command)
                    {
                        case "ls":
                            ListDirectory();
                            break;
                        case "cd":
                            ChangeDirectory(argument);
                            break;
                        case "back":
                            GoBack();
                            break;
                        case "size":
                            ShowSize();
                            break;
                        case "help":
                            ShowHelp();
                            break;
                        case "exit":
                        case "quit":
                            return;
                        default:
                            Console.WriteLine($"Onbekend commando: {command}. Type 'help' voor beschikbare commando's.");
                            break;
                    }
                }
                catch (UnauthorizedAccessException)
                {
                    Console.WriteLine("Error: toegang geweigerd.");
                }
                catch (DirectoryNotFoundException)
                {
                    Console.WriteLine("Error: Directory niet gevonden.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Error: {ex.Message}");
                }

                Console.WriteLine();
            }
        }

        static void ListDirectory()
        {
            var dirInfo = new DirectoryInfo(currentDirectory);

            // Directorys
            var directories = dirInfo.GetDirectories();
            if (directories.Length > 0)
            {
                Console.WriteLine("Directorty:");
                foreach (var dir in directories.OrderBy(d => d.Name))
                {
                    Console.WriteLine($"  [DIR]  {dir.Name}");
                }
            }

            // bestaden
            var files = dirInfo.GetFiles();
            if (files.Length > 0)
            {
                Console.WriteLine("\nFiles:");
                foreach (var file in files.OrderBy(f => f.Name))
                {
                    Console.WriteLine($"  [FILE] {file.Name} ({FormatSize(file.Length)})");
                }
            }

            if (directories.Length == 0 && files.Length == 0)
            {
                Console.WriteLine("(lege directory)");
            }
        }

        static void ChangeDirectory(string path)
        {
            if (string.IsNullOrEmpty(path))
            {
                Console.WriteLine("Usage: cd <path>");
                return;
            }

            string newPath;

            if (Path.IsPathRooted(path))
            {
                newPath = path;
            }
            else
            {
                newPath = Path.Combine(currentDirectory, path);
            }

            newPath = Path.GetFullPath(newPath);

            if (Directory.Exists(newPath))
            {
                directoryHistory.Push(currentDirectory);
                currentDirectory = newPath;
                Console.WriteLine($"veranderd naar: {currentDirectory}");
            }
            else
            {
                Console.WriteLine($"Directory niet gevonden: {newPath}");
            }
        }

        static void GoBack()
        {
            if (directoryHistory.Count > 0)
            {
                currentDirectory = directoryHistory.Pop();
                Console.WriteLine($"terug naar: {currentDirectory}");
            }
            else
            {
                Console.WriteLine("Geen vorige directory in geschiedenis.");
            }
        }

        static void ShowSize()
        {
            long totalSize = CalculateDirectorySize(currentDirectory);
            Console.WriteLine($"totale grote van '{currentDirectory}': {FormatSize(totalSize)}");
        }

        static long CalculateDirectorySize(string directoryPath)
        {
            long size = 0;

            try
            {
                var dirInfo = new DirectoryInfo(directoryPath);

                foreach (var file in dirInfo.GetFiles())
                {
                    try
                    {
                        size += file.Length;
                    }
                    catch (Exception)
                    {
                    }
                }

                foreach (var subDir in dirInfo.GetDirectories())
                {
                    try
                    {
                        size += CalculateDirectorySize(subDir.FullName);
                    }
                    catch (Exception)
                    {
                    }
                }
            }
            catch (Exception)
            {
            }

            return size;
        }

        static string FormatSize(long bytes)
        {
            string[] sizes = { "B", "KB", "MB", "GB", "TB" };
            double len = bytes;
            int order = 0;

            while (len >= 1024 && order < sizes.Length - 1)
            {
                order++;
                len = len / 1024;
            }

            return $"{len:0.##} {sizes[order]}";
        }

        static void ShowHelp()
        {
            Console.WriteLine("Available commands:");
            Console.WriteLine("  ls         - lijst van content van de huidige directory");
            Console.WriteLine("  cd <path>  - Verander directory (absolute or relative path)");
            Console.WriteLine("  back       - Ga terug naar vorige directory");
            Console.WriteLine("  size       - Toon totale grootte van huidige directory en subdirectories");
            Console.WriteLine("  help       - Toon dit helpbericht");
            Console.WriteLine("  exit/quit  - Verlaat het programma");
        }
    }
}
