/**
 * Get configuration by app name.
 *
 * @param {string} [app] - App name. Default: fireedge
 * @param {GetConfigurationOptions} options - Options
 * @returns {object} Configuration
 */
const getConfiguration = (
  app = defaultAppName,
  { onError = defaultEmptyFunction, includeProtectedConfig = true } = {}
) => {
  const config = readYAMLFile(getConfigPathByApp(app), onError)

  if (config && !includeProtectedConfig) {
    return filterByProtectedKeys(config, getProtectedKeysByApp(app))
  }

  return config
}
/**
 * Get FireEdge configuration.
 *
 * @param {GetConfigurationOptions} [options] - Options
 * @returns {object} FireEdge configuration
 */
const getFireedgeConfig = (options) => getConfiguration(defaultAppName, options)
