package com.ruinshe;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.HashMap;
import java.util.Map;

public class Main {

  private static final String OUTPUT_FOLDER_NAME = "output";
  private static String[] SUPPORTED_EXTENSIONS = {".c", ".cpp", ".pas"};

  public static void main(String[] args) {

    for (String arg : args) {
      if (arg.startsWith("--help")) {
        System.out.println("java -jar sourceHelper.jar [--source=sources] [--problem=name]\n"
            + "\tby default source folder is ./sources\n"
            + "\tthe problem argument is repeated.\n"
            + "\te.g. java -jar sourceHelper.jar --problem=prime --problem=count");
        return;
      }
    }

    String sourceFolderName = "sources";
    Map<String, Integer> sourceFiles = new HashMap<String, Integer>();
    Map<String, String> sourceFileToProblemNameMap = new HashMap<String, String>();
    int problemCount = 0;
    for (String arg : args) {
      if (arg.startsWith("--source")) {
        String[] arr = arg.split("=");
        if (arr.length != 2) {
          throw new RuntimeException(
              "The problem format should be --source=source_folder_name.");
        }
        sourceFolderName = arr[1];
      } else if (arg.startsWith("--problem")) {
        String[] arr = arg.split("=");
        if (arr.length != 2) {
          throw new RuntimeException(
              "The problem format should be --problem=problem_name.");
        }
        for (String extension : SUPPORTED_EXTENSIONS) {
          sourceFiles.put(arr[1] + extension, problemCount);
          sourceFileToProblemNameMap.put(arr[1] + extension, arr[1]);
        }
        problemCount++;
      }
    }
    System.err.printf("supported source files: %s\n", sourceFiles.keySet().toString());

    // Before iterating the files in current folder,
    // create the output folder if it doesn't exist.
    File outputFolder = new File(OUTPUT_FOLDER_NAME);
    createFolder(outputFolder);

    File folder = new File(sourceFolderName);

    if (!folder.isDirectory()) {
      throw new RuntimeException("file '" + folder.getAbsolutePath()
          + "' is not a folder.");
    }

    for (File sourceFolder : folder.listFiles()) {
      if ("output".equals(sourceFolder.getName())) {
        // skip the output folder.
        continue;
      }
      if (sourceFolder.isDirectory()) {
        File distFolder = new File(outputFolder.getAbsolutePath()
            + "/" + sourceFolder.getName());
        createFolder(distFolder);
        boolean[] copied = new boolean[problemCount];
        int copiedFiles = 0;
        for (File sourceFile : sourceFolder.listFiles()) {
          Integer id = sourceFiles.get(sourceFile.getName());
          if (id != null) {
            createFolder(distFolder + "/"
                + sourceFileToProblemNameMap.get(sourceFile.getName()));
            File distFile = new File(distFolder + "/"
                + sourceFileToProblemNameMap.get(sourceFile.getName())
                + "/" + sourceFile.getName());
            try {
              Files.copy(sourceFile.toPath(), distFile.toPath());
            } catch (IOException e) {
              e.printStackTrace();
            }
            if (!copied[id]) {
              copiedFiles++;
              copied[id] = true;
            }
          }
        }
        if (copiedFiles != problemCount) {
          System.err.printf("only %d of %d solutions found in %s\n",
              copiedFiles, problemCount, sourceFolder.getAbsolutePath());
        }
      }
    }
  }

  private static void createFolder(File folder) {
    if (!folder.exists() && !folder.mkdirs()
        || folder.exists() && !folder.isDirectory()) {
      throw new RuntimeException("Creating folder '"
          + folder.getAbsolutePath() + "' failed.");
    }
  }

  private static void createFolder(String path) {
    createFolder(new File(path));
  }
}
