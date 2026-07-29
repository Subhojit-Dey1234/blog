import React, { useEffect, useState } from "react";
import { createRoot } from "react-dom/client";
import ExcalidrawLib from "@excalidraw/excalidraw/dist/excalidraw.production.min.js";
import "./styles.css";

const { Excalidraw } = ExcalidrawLib;

function getMkdocsTheme() {
  return document.body.getAttribute("data-md-color-scheme") === "slate" ? "dark" : "light";
}

function ExcalidrawEmbed({ src }) {
  const [scene, setScene] = useState(null);
  const [theme, setTheme] = useState(getMkdocsTheme());

  useEffect(() => {
    fetch(src)
      .then((r) => r.json())
      .then(setScene)
      .catch((err) => console.error("Failed to load excalidraw scene", src, err));
  }, [src]);

  useEffect(() => {
    const observer = new MutationObserver(() => setTheme(getMkdocsTheme()));
    observer.observe(document.body, {
      attributes: true,
      attributeFilter: ["data-md-color-scheme"],
    });
    return () => observer.disconnect();
  }, []);

  if (!scene) {
    return <div className="excalidraw-loading">Loading drawing…</div>;
  }

  return (
    <Excalidraw
      initialData={{
        elements: scene.elements,
        appState: { ...scene.appState, theme },
        scrollToContent: true,
      }}
      viewModeEnabled
      theme={theme}
    />
  );
}

function assetBase() {
  const script = Array.from(document.getElementsByTagName("script")).find((s) =>
    s.src.includes("excalidraw-viewer.js")
  );
  return script ? script.src.replace(/assets\/js\/excalidraw-viewer\.js.*$/, "") : "";
}

function mount(el) {
  const src = assetBase() + el.dataset.src;
  createRoot(el).render(<ExcalidrawEmbed src={src} />);
}

function init() {
  window.EXCALIDRAW_ASSET_PATH = assetBase() + "assets/js/";
  document.querySelectorAll(".excalidraw-embed:not([data-mounted])").forEach((el) => {
    el.setAttribute("data-mounted", "true");
    mount(el);
  });
}

if (document.readyState === "loading") {
  document.addEventListener("DOMContentLoaded", init);
} else {
  init();
}
