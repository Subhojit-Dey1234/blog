import { cpSync, existsSync } from "fs";
import { fileURLToPath } from "url";
import path from "path";

const __dirname = path.dirname(fileURLToPath(import.meta.url));
const src = path.join(__dirname, "..", "node_modules", "@excalidraw", "excalidraw", "dist", "excalidraw-assets");
const dest = path.join(__dirname, "..", "..", "docs", "assets", "js", "excalidraw-assets");

if (!existsSync(src)) {
  console.error("excalidraw-assets not found at", src);
  process.exit(1);
}

cpSync(src, dest, { recursive: true });
console.log("Copied excalidraw-assets to", dest);
