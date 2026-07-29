import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

export default defineConfig({
  plugins: [react()],
  define: {
    "process.env.NODE_ENV": JSON.stringify("production"),
    "process.env.IS_PREACT": JSON.stringify("false"),
  },
  build: {
    outDir: "../docs/assets/js",
    emptyOutDir: false,
    cssCodeSplit: false,
    lib: {
      entry: "src/main.jsx",
      name: "ExcalidrawViewer",
      formats: ["iife"],
      fileName: () => "excalidraw-viewer.js",
    },
    rollupOptions: {
      output: {
        assetFileNames: "excalidraw-viewer.[ext]",
      },
    },
  },
});
