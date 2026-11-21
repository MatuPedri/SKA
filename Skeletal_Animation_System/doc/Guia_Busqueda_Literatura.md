# Guía: la parte de la literature review que tenés que hacer vos

El documento `Literature_Review_SKA.docx` es un borrador. La sección 2 (Search Strategy) describe un proceso de búsqueda: **tenés que hacerlo de verdad** y ajustar el texto a lo que hiciste. Esta guía sigue los pasos de la guía de SHU (Dawson 2015, cap. 5, y https://libguides.shu.ac.uk/literaturereviews).

## Paso 1. Armar tu hoja de seguimiento (15 min)

Creá una tabla (Excel o Notion) con estas columnas. Es la base de todo lo demás.

| Fuente (APA) | Dónde la encontré | Tema (A/B/contexto) | Leída (resumen / completa) | Cómo ayuda al proyecto | Limitaciones |
|---|---|---|---|---|---|

Cada vez que una fuente merezca una lectura más larga, agregá su referencia APA. Podés usar Zotero, el gestor de SHU (https://libguides.shu.ac.uk/referencing/tools) o la herramienta de referencias de Word.

## Paso 2. Búsqueda amplia: libros y papers generales

1. Conseguí los tres libros de la sección 2 (Parent 2012, Gregory 2018, Akenine-Möller et al. 2018). Buscalos en el catálogo de la biblioteca de SHU; muchos están como libro electrónico.
2. Leé los capítulos de animación esquelética y skinning. Mientras leés, anotá los nombres de papers que citan.
3. Anotá en la hoja qué libros leíste y qué capítulos.

## Paso 3. Estrechar a dos temas

Con lo leído, confirmá que tus dos temas siguen siendo los correctos:

- **Tema A: skinning y calidad.** Qué técnicas hay, qué artefactos tiene LBS.
- **Tema B: implementación y rendimiento CPU vs GPU.** Cómo se implementa y qué se sabe de su costo.

Si al leer ves que el foco real es otro, cambiá los temas y la review.

## Paso 4. Búsquedas específicas (la parte más importante)

Buscá en **Google Scholar**, **ACM Digital Library**, **IEEE Xplore** y la **búsqueda de la biblioteca de SHU**. Anotá en la hoja qué base y qué términos usaste.

**Tema A, términos sugeridos:**
- "linear blend skinning" artifacts
- "skeletal subspace deformation"
- "dual quaternion skinning"
- "skinning" survey real-time
- "quaternion interpolation" animation

**Tema B, términos sugeridos (el más flojo hoy):**
- "GPU skinning" performance
- "skinning" CPU GPU comparison
- "vertex skinning" benchmark
- "crowd rendering" GPU skinning
- "skinned instancing"
- "GPU benchmarking" methodology frame time
- glTF skinning OpenGL

Para cada búsqueda:
1. Leé los títulos y abstracts de los primeros resultados.
2. Si algo parece útil, leé la introducción y las conclusiones.
3. Si vale la pena, leelo entero y agregalo a la hoja.
4. Mirá su bibliografía (**backward snowballing**) y, en Google Scholar, "Citado por" (**forward snowballing**).

**Meta:** que el tema B tenga al menos 2 a 4 fuentes más específicas sobre rendimiento de skinning o benchmarking de GPU. Si no encontrás ninguna, eso es un hallazgo válido: dejalo escrito como "no se encontró evidencia" y justifica por qué tu benchmark aporta.

## Paso 5. Criterios para aceptar una fuente

- Paper de revista o congreso revisado por pares, libro académico o curso reconocido (como los de SIGGRAPH).
- Material de industria (charlas, blogs, documentación) solo si es la fuente original de una técnica, y decilo en el texto.
- Fecha y autoridad: preferí trabajos citados por otros.

## Paso 6. Verificar el borrador que te di

Las referencias del documento las escribí de memoria. Para **cada una**:
- [ ] Existe (buscá el título en Scholar).
- [ ] Autores, año, revista/congreso, páginas y DOI son correctos. Los que dejé sin DOI, completalos.
- [ ] Lo que digo de ese trabajo es cierto. Leé al menos el abstract y las conclusiones. Si no podés respaldar una afirmación, cambiala o sacala.
- [ ] Especial atención a: Dudash (2007), Lander (1998), Magnenat-Thalmann et al. (1988) y Shoemake (1985).

## Paso 7. Reescribir la sección 2 con lo que realmente hiciste

Ajustá en el documento:
- Las bases que usaste de verdad.
- Los términos reales (actualizá la Tabla 1).
- Qué libros usaste como punto de partida y cuál fue el paper pivote para el snowballing.
- Fechas de búsqueda y criterios de inclusión y exclusión que aplicaste.

## Paso 8. Completar la bibliografía anotada

El apéndice ya tiene una anotación borrador para cada fuente. Para cada una, **reescribila con tus palabras** después de leerla:
- Cómo te ayudó a entender el problema.
- Cómo influyó en tu solución (por ejemplo, "usé su fórmula de skinning en el shader").
- Qué limitaciones tiene.

## Paso 9. Revisión final

- [ ] Todas las citas del texto están en la lista de referencias, y viceversa.
- [ ] El formato es APA 7 en todo.
- [ ] Revisaste ortografía y la Tabla 2.
- [ ] Actualizaste la tabla de contenidos en Word (clic derecho, Update field).
- [ ] Completaste la fecha de la portada.
- [ ] Confirmaste con Philip Alassad o con Blackboard el límite de palabras y el formato.
- [ ] Todo el texto lo entendés y podés defenderlo: lo que no entiendas, sacalo.

## Cuando termines

Pasame las fuentes nuevas que encontraste (sobre todo las del tema B) y actualizo la review para incorporarlas.
